#ifndef TEST_LINE_H
# define TEST_LINE_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include "line.h"

# define TEST_START() test_start(__func__)
# define TEST_END(res) test_end(__func__, (res))

# define TEST_STR_RUN "\e[1;36m[RUN   ]\e[m"
# define TEST_STR_OK "\e[1;32m[    OK]\e[m"
# define TEST_STR_FAIL "\e[1;31m[  FAIL]\e[m"
# define TEST_DIF_PLUS "\e[32m+ %s\n\e[m"
# define TEST_DIF_MINUS "\e[31m- %s\n\e[m"
# define TEST_FILE_LINE "\e[33m%s:%d\e[m"
# define TEST_FROM ">>> %s:%d\n"

void	test_printarr(char **arr, char *sep)
{
	int	i;
	int	n;

	n = 0;
	while (arr[n] != NULL)
		++n;
	i = 0;
	while (i < n)
	{
		fprintf(stderr, "%s", arr[i]);
		if (i + 1 < n)
			fprintf(stderr, "%s", sep);
		++i;
	}
}

void	test_line_print(const t_line *line)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (i < line->size)
	{
		prog = &line->progs[i];
		if (prog->in_redir.name != NULL)
			fprintf(stderr, "<%s ", prog->in_redir.name);
		test_printarr(prog->args, "\033[1;30m·\033[0;m");
		if (prog->out_redir.name != NULL)
			fprintf(stderr, " >%s", prog->out_redir.name);
		if (i + 1 < line->size)
			fprintf(stderr, " | ");
		++i;
	}
	fprintf(stderr, "\n");
}


int	test_strarr_eq(char **actual, char **expected)
{
	int	i;

	i = 0;
	while (actual[i] != NULL && expected[i] != NULL)
	{
		if (strcmp(actual[i], expected[i]) != 0)
			return (0);
		++i;
	}
	return (actual[i] == expected[i]);
}

int	test_redir_eq(t_redir *actual, t_redir *expected)
{	
	if (actual->name == NULL || expected->name == NULL)
		return (actual->name == expected->name);
	else
		return (strcmp(actual->name, expected->name) == 0);	
}

int	test_prog_eq(t_prog *actual, t_prog *expected)
{
	if (!test_redir_eq(&actual->in_redir, &expected->in_redir))
		return (0);
	if (!test_redir_eq(&actual->out_redir, &expected->out_redir))
		return (0);
	if (!test_strarr_eq(actual->args, expected->args))
		return (0);
	return (1);
}

int	test_line_eq(t_line *actual, t_line *expected)
{
	int	i;

	if (actual->size != expected->size)
		return (0);
	i = 0;
	while (i < actual->size)
	{
		if (!test_prog_eq(&actual->progs[i], &expected->progs[i]))
			return (0);
		++i;
	}
	return (1);
}

int	test_line_eq_print(t_line *actual, t_line *expected)
{
	int	eq;

	eq = test_line_eq(actual, expected);
	if (!eq)
	{
		fprintf(stderr, "Lines don't match:\n");
		fprintf(stderr, "Actual  : ");
		test_line_print(actual);
		fprintf(stderr, "Expected: ");
		test_line_print(expected);
	}
	return (eq);
}


#define test_expect_retval(...) test_expect_retval_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_retval_x(const char *from, int line, int actual, int expected)
{
	if (actual != expected)
	{
		fprintf(stderr, TEST_FROM, from, line);
		fprintf(stderr, "Return value does not match:\n");
		fprintf(stderr, "Actual  : %d\n", actual);
		fprintf(stderr, "Expected: %d\n", expected);
	}
	return (actual == expected);
}

char *test_getline(FILE *file)
{
	char *line;
	ssize_t size;
	size_t	n;

	line = NULL;
	n = 0;
	size = getline(&line, &n, file);
	if (size < 0)
	{
		free(line);
		return (NULL);
	}
	if (line[size - 1] == '\n')
		line[size - 1] = '\0';
	return (line);
}


#define test_expect_file_content(...) test_expect_file_content_x(__FILE__, __LINE__, __VA_ARGS__)
int	test_expect_file_content_x(const char *from, int line, const char *filename, ...)
{
	va_list vargs;
	char	*refline;
	char	*actline;
	FILE	*file;
	int		res;
	int		i;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "%s: %s\n", filename, strerror(errno));
		return (0);
	}
	res = 0;
	i = 1;
	va_start(vargs, filename);
	while (1)
	{
		refline = va_arg(vargs, char*);
		actline = test_getline(file);
		if (refline == NULL || actline == NULL)
		{
			if (refline == actline)
				res = 1;
			else if (actline == NULL)
				fprintf(stderr, TEST_FROM TEST_FILE_LINE " EOF was not expected\n",
					from, line, filename, i);
			else
				fprintf(stderr, TEST_FILE_LINE " EOF was expected\n", filename, i);
			break;
		}
		if (strcmp(refline, actline) != 0)
		{
			fprintf(stderr, TEST_FROM TEST_FILE_LINE " does not match expected output\n",
				from, line, filename, i);
			fprintf(stderr, TEST_DIF_PLUS, actline);
			fprintf(stderr, TEST_DIF_MINUS, refline);
			break;
		}
		++i;
		free(actline);
	}
	free(actline);
	va_end(vargs);
	fclose(file);
	return (res);
}

void	test_prog_args(t_prog *prog, int size, ...)
{
	int		i;
	va_list vargs;

	prog->args = calloc(size + 1, sizeof(char *));
	prog->args[size] = NULL;
	va_start(vargs, size);
	i = 0;
	while (i < size)
		prog->args[i++] = strdup(va_arg(vargs, char*));
	va_end(vargs);
}

void	test_prog_redirs(t_prog *prog, const char *in, const char *out)
{
	if (in != NULL)
		prog->in_redir.name = strdup(in);
	else
		prog->in_redir.name = NULL;
	if (out != NULL)
		prog->out_redir.name = strdup(out);
	else
		prog->out_redir.name = NULL;
}

void	test_line_init(t_line *line, int size)
{
	line->size = size;
	line->progs = calloc(size, sizeof(t_prog));
}

void	test_line_end(t_line *line, int it)
{
	if (line->size != it)
	{
		fprintf(stderr, "Error: Number of initialized line->progs (%d)"
			" doesn't match line->size (%d)\n",
			it, line->size);
		exit(1);
	}
}

int	test_redirect_stdout(const char *filename)
{
	int	redir_fd;
	int	stdout_fd;

	redir_fd = creat(filename, 0644);
	if (redir_fd < 0)
	{
		fprintf(stderr, "%s: %s\n", filename, strerror(errno));
		exit(1);
	}
	stdout_fd = dup(1);
	dup2(redir_fd, 1);
	close(redir_fd);
	return (stdout_fd);
}

void	test_restore_stdout(int stdout_fd)
{
	dup2(stdout_fd, 1);
	close(stdout_fd);
}

void	test_start(const char *test_name)
{
	fprintf(stderr, "%s %s\n", TEST_STR_RUN, test_name);
}

int	test_end(const char *test_name, int success)
{
	if (success)
		fprintf(stderr, "%s %s\n", TEST_STR_OK, test_name);
	else
		fprintf(stderr, "%s %s\n", TEST_STR_FAIL, test_name);
	return (success);
}

#endif