#ifndef TEST_LINE_H
# define TEST_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include "line.h"

static void	test_printarr(char **arr, char *sep)
{
	int	i;
	int	n;

	n = 0;
	while (arr[n] != NULL)
		++n;
	i = 0;
	while (i < n)
	{
		printf("%s", arr[i]);
		if (i + 1 < n)
			printf("%s", sep);
		++i;
	}
}

static void	test_line_print(const t_line *line)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (i < line->size)
	{
		prog = &line->progs[i];
		if (prog->in_redir.name != NULL)
			printf("<%s ", prog->in_redir.name);
		test_printarr(prog->args, "\033[1;30m·\033[0;m");
		if (prog->out_redir.name != NULL)
			printf(" >%s", prog->out_redir.name);
		if (i + 1 < line->size)
			printf(" | ");
		++i;
	}
	printf("\n");
}


static int	test_strarr_eq(char **actual, char **expected)
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

static int	test_redir_eq(t_redir *actual, t_redir *expected)
{	
	if (actual->name == NULL || expected->name == NULL)
		return (actual->name == expected->name);
	else
		return (strcmp(actual->name, expected->name) == 0);	
}

static int	test_prog_eq(t_prog *actual, t_prog *expected)
{
	if (!test_redir_eq(&actual->in_redir, &expected->in_redir))
		return (0);
	if (!test_redir_eq(&actual->out_redir, &expected->out_redir))
		return (0);
	if (!test_strarr_eq(actual->args, expected->args))
		return (0);
	return (1);
}

static int	test_line_eq(t_line *actual, t_line *expected)
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

static int	test_line_eq_print(t_line *actual, t_line *expected)
{
	int	eq;

	eq = test_line_eq(actual, expected);
	if (!eq)
	{
		printf("Lines don't match:\n");		
		printf("Actual  : ");
		test_line_print(actual);
		printf("Expected: ");
		test_line_print(expected);
	}
	return (eq);
}

static void	test_prog_args(t_prog *prog, int size, ...)
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

static void	test_prog_redirs(t_prog *prog, const char *in, const char *out)
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

static void	test_line_init(t_line *line, int size)
{
	line->size = size;
	line->progs = calloc(size, sizeof(t_prog));
}

static void	test_line_end(t_line *line, int it)
{
	if (line->size != it)
	{
		printf("Error: Number of initialized line->progs (%d)"
			" doesn't match line->size (%d)\n",
			it, line->size);
		exit(1);
	}
}

static void	test_start(const char *test_name)
{
	printf("[RUN   ] %s\n", test_name);
}

static int	test_end(const char *test_name, int success)
{
	if (success)
		printf("[    OK] %s\n", test_name);
	else
		printf("[  FAIL] %s\n", test_name);
	return (success);
}

#endif