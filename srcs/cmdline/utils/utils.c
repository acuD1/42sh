/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/16 17:14:43 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <term.h>

void			xtputs(char *str, int i, int (*f)(int))
{
	t_core	*shell;

	shell = get_core(NULL);
	tputs(str, i, f);
}

static ssize_t	get_width(ssize_t buff_i, ssize_t w, ssize_t y, t_read *term)
{
	if (buff_i == -1)
	{
		w += term->prompt_len;
		if ((w - (term->ws_col * y)) >= term->ws_col)
			y++;
	}
	if (y == 0)
		y = 1;
	if (w >= term->ws_col)
		w = w - (term->ws_col * y);
	return (w);
}

ssize_t			get_width_last_line(t_read *term)
{
	ssize_t	buff_index;
	ssize_t	w;
	ssize_t	y;
	ssize_t	i;

	w = 0;
	i = 0;
	y = 0;
	buff_index = term->x_index - (ssize_t)term->prompt_len;
	if ((buff_index > 0) && term->buffer[buff_index - 1] == '\n')
		buff_index--;
	else
		return (term->ws_col - 1);
	while (buff_index-- > 0 && term->buffer[buff_index] != '\n')
	{
		if (i >= term->ws_col)
		{
			y++;
			i = -1;
		}
		i++;
		w++;
	}
	w = get_width(buff_index, w, y, term);
	return (w);
}

ssize_t			get_width_current_line(t_read *term)
{
	ssize_t	buff_index;
	ssize_t	width;
	ssize_t	x;

	width = 0;
	x = term->x;
	buff_index = term->x_index - (ssize_t)term->prompt_len;
	while (buff_index >= 0 && buff_index < (ssize_t)ft_strlen(term->buffer))
	{
		if (term->buffer[buff_index] == '\n' || x == (term->ws_col - 1))
			break ;
		width++;
		x++;
		buff_index++;
	}
	width += term->x;
	return (width);
}

u_int64_t		get_mask(const char *buff)
{
	u_int16_t	i;
	u_int16_t	shift;
	u_int64_t	value;
	u_int64_t	tmp;

	i = 0;
	tmp = 0;
	value = 0;
	shift = 56;
	while (i < 8 && buff && buff[i])
	{
		value = (u_int64_t)buff[i];
		value <<= shift;
		tmp |= value;
		shift -= 8;
		i++;
	}
	return (tmp);
}
