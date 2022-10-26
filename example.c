/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:12:03 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/26 20:30:30 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "test_line.h"

t_line	dummy_parser(const char * line_str)
{	
	t_line	line;
	int		i;

	(void)line_str;
	i = 0;
	test_line_init(&line, 2);
	test_prog_args(&line.progs[i], 2, "ls", "-l");
	test_prog_redirs(&line.progs[i++], "in.txt", NULL);
	test_prog_args(&line.progs[i], 2, "grep", "total");
	test_prog_redirs(&line.progs[i++], NULL, "out.txt");
	test_line_end(&line, i);
	return (line);
}

t_line simplest_parser(char *line_str)
{
	t_line	line;

	line.size = 1;
	line.progs = malloc(sizeof(t_prog));
	line.progs[0].args = calloc(2, sizeof(char *));
	line.progs[0].args[0] = strdup(line_str);
	line.progs[0].args[1] = NULL;
	line.progs[0].in_redir.path = NULL;
	line.progs[0].out_redir.path = NULL;
	return (line);
}


int	test_simplest(void)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START();
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], 1, "ls");
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = simplest_parser("ls");
	res = test_line_eq_print(&line, &expect);
	return (TEST_END(res));
}

int	test_bit_harder(void)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START();
	i = 0;
	test_line_init(&expect, 1);
	test_prog_args(&expect.progs[i], 2, "grep", "total");
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = simplest_parser("grep total");
	res = test_line_eq_print(&line, &expect);
	return (TEST_END(res));
}

int	test_dummy_passing(void)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START();
	i = 0;
	test_line_init(&expect, 2);
	test_prog_args(&expect.progs[i], 2, "ls", "-l");
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_prog_args(&expect.progs[i], 2, "grep", "total");
	test_prog_redirs(&expect.progs[i++], NULL, "out.txt");
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");
	res = test_line_eq_print(&line, &expect);
	return (TEST_END(res));
}

int	test_dummy_not_passing(void)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START();
	i = 0;
	test_line_init(&expect, 3);
	test_prog_args(&expect.progs[i], 2, "ls", "-l");
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_prog_args(&expect.progs[i], 2, "grep", "total");
	test_prog_redirs(&expect.progs[i++], NULL, "out.txt");
	test_prog_args(&expect.progs[i], 2, "wc", "-l");
	test_prog_redirs(&expect.progs[i++], NULL, NULL);
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");
	res = test_line_eq_print(&line, &expect);
	return (TEST_END(res));
}

int	test_dummy_broken(void)
{
	t_line	line;
	t_line	expect;
	int		i;
	int		res;

	TEST_START();
	i = 0;
	test_line_init(&expect, 3);
	test_prog_args(&expect.progs[i], 2, "ls", "-l");
	test_prog_redirs(&expect.progs[i++], "in.txt", NULL);
	test_line_end(&expect, i);
	line = dummy_parser("<in.txt ls -l | grep total >out.txt");	
	res = test_line_eq_print(&line, &expect);
	return (TEST_END(res));
}

int (*const test_functions[])() = {
	test_simplest,
	test_bit_harder,
    test_dummy_not_passing,
    test_dummy_passing,
	// test_dummy_broken,
    NULL
};

int	main(void)
{
	int	passed;
	int	total;

	passed = 0;
	total = 0;
	while (test_functions[total] != NULL)
	{
		passed += test_functions[total]();
		++total;
	}
	printf("^^^\n");
	if (passed == total)
		printf("    %s all %d tests passed\n", TEST_STR_OK, total);
	else
		printf("    %s %d of %d tests failed\n", TEST_STR_FAIL,
			total - passed, total);
	printf("^^^\n");
	return (passed < total);
}
