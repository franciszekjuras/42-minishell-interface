/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:03:30 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 11:03:31 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft/libft.h>
#include "line.h"

void	prog_args(t_prog *prog, int size, ...)
{
	int		i;
	va_list vargs;

	prog->args = ft_calloc(size + 1, sizeof(char *));
	prog->args[size] = NULL;
	va_start(vargs, size);
	i = 0;
	while (i < size)
		prog->args[i++] = ft_strdup(va_arg(vargs, char*));
	va_end(vargs);
}

void	prog_redirs(t_prog *prog, const char *in, const char *out)
{
	if (in != NULL)
		prog->in_redir.name = ft_strdup(in);
	else
		prog->in_redir.name = NULL;
	if (out != NULL)
		prog->out_redir.name = ft_strdup(out);
	else
		prog->out_redir.name = NULL;
}

void	line_init(t_line *line, int size)
{
	line->size = size;
	line->progs = ft_calloc(size, sizeof(t_prog));
}
