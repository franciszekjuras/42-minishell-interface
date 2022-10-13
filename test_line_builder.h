/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line_builder.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:05:07 by fjuras            #+#    #+#             */
/*   Updated: 2022/10/13 12:30:14 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LINE_BUILDER_H
# define TEST_LINE_BUILDER_H

#include "line.h"

void	prog_args(t_prog *prog, int size, ...);

void	prog_redirs(t_prog *prog, const char *in, const char *out);

void	line_init(t_line *line, int size);

#endif
