/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line_eq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:40:13 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 12:31:46 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "line.h"

static int	strarr_eq(char **actual, char **expected)
{
	int	i;

	i = 0;
	while (actual[i] != NULL && expected[i] != NULL)
	{
		if (ft_strcmp(actual[i], expected[i]) != 0)
			return (0);
		++i;
	}
	return (actual[i] == expected[i]);
}

static int	redir_eq(t_redir *actual, t_redir *expected)
{	
	if (actual->name == NULL || expected->name == NULL)
		return (actual->name == expected->name);
	else
		return (ft_strcmp(actual->name, expected->name) == 0);	
}

static int	prog_eq(t_prog *actual, t_prog *expected)
{
	if (!redir_eq(&actual->in_redir, &expected->in_redir))
		return (0);
	if (!redir_eq(&actual->out_redir, &expected->out_redir))
		return (0);
	if (!strarr_eq(actual->args, expected->args))
		return (0);
	return (1);
}

int	line_eq(t_line *actual, t_line *expected)
{
	int	i;

	if (actual->size != expected->size)
		return (0);
	i = 0;
	while (i < actual->size)
	{
		if (!prog_eq(&actual->progs[i], &expected->progs[i]))
			return (0);
		++i;
	}
	return (1);
}
