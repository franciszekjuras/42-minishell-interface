/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:50:14 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 12:30:28 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

typedef struct s_redir
{
	char	*name;
}	t_redir;


typedef struct s_prog
{
	t_redir	in_redir;
	t_redir	out_redir;
	char	**args;
}	t_prog;


typedef struct s_line
{
	t_prog	*progs;
	int		size;
}	t_line;

#endif
