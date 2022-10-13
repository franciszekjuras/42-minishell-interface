/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:02:01 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 12:06:36 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "line.h"

static void	ft_dprintarr(int fd, char **arr, char *sep)
{
	int	i;
	int	n;

	n = 0;
	while (arr[n] != NULL)
		++n;
	i = 0;
	while (i < n)
	{
		ft_putstr_fd(arr[i], fd);
		if (i + 1 < n)
			ft_putstr_fd(sep, fd);
		++i;
	}
}

void	line_print(const t_line *line)
{
	int		i;
	t_prog	*prog;

	i = 0;
	while (i < line->size)
	{
		prog = &line->progs[i];
		if (prog->in_redir.name != NULL)
			ft_printf("<%s ", prog->in_redir.name);
		ft_dprintarr(1, prog->args, "\033[1;30m·\033[0;m");
		if (prog->out_redir.name != NULL)
			ft_printf(" >%s", prog->out_redir);
		if (i + 1 < line->size)
			ft_printf(" | ");
		++i;
	}
	ft_printf("\n");
}
