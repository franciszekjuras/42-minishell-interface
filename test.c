/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:12:03 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 12:59:45 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "line.h"
#include "test_line_eq.h"
#include "test_line_builder.h"
#include "test_line_print.h"


int	main(void)
{
	t_line	line;
	t_line	expect;
	int		i;

	line_init(&line, 2);
	i = 0;
	prog_args(&line.progs[i], 2, "ls", "-l");
	prog_redirs(&line.progs[i++], "in.txt", NULL);
	prog_args(&line.progs[i], 2, "grep", "total");
	prog_redirs(&line.progs[i++], NULL, "out.txt");
	line_print(&line);
	line_init(&expect, 3);
	i = 0;
	prog_args(&expect.progs[i], 2, "ls", "-l");
	prog_redirs(&expect.progs[i++], "in.txt", NULL);
	prog_args(&expect.progs[i], 2, "grep", "total");
	prog_redirs(&expect.progs[i++], NULL, "out.txt");	
	prog_args(&expect.progs[i], 2, "wc", "-l");
	prog_redirs(&expect.progs[i++], NULL, NULL);
	line_print(&expect);
	if (line_eq(&line, &expect))
		ft_printf("OK\n");
	else	
		ft_printf("KO\n");
}