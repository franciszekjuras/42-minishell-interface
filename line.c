/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/22 20:16:30 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line.h"

void	args_free(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		free(args[i++]);
	free(args);
}

void	line_free(t_line line)
{
	int	i;

	i = 0;
	while (i < line.size)
	{
		args_free(line.progs[i].args);
		++i;
	}
	free(line.progs);
}
