/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/26 10:18:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

uint8_t		get_width_last_line(t_read *term)
{
	int	buff_index;
	int	width;
	int	x;

	width = 0;
	x = term->x + 1;
	buff_index = term->x_index - term->prompt_len - 1;
	while (--buff_index)
	{
		if (term->buffer[buff_index] == '\n')
			break ;
		else if (x == 0 && !ft_strchr(term->buffer, '\n'))
			return (term->ws_col - 1);
		x--;
		width++;
	}
	if (width > term->ws_col)
		width -= term->ws_col;
	if (term->y == 1)
		width += term->prompt_len;
	return (width);
}

uint8_t		get_width_current_line(t_read *term)
{
	int	buff_index;
	int	width;
	int	x;

	width = 0;
	x = term->x;
	buff_index = term->x_index - term->prompt_len;
	while (term->buffer[buff_index])
	{
		if (term->buffer[buff_index] == NEW_LINE || x == term->ws_col - 1)
			break ;
		width++;
		x++;
		buff_index++;
	}
	width += term->x;
	return (width);
}

uint64_t	get_mask(char *buff)
{
	uint16_t	i;
	uint16_t	shift;
	uint64_t	value;
	uint64_t	tmp;

	i = 0;
	tmp = 0;
	value = 0;
	shift = 56;
	while (i < 8 && buff[i])
	{
		value = buff[i];
		value <<= shift;
		tmp |= value;
		shift -= 8;
		i++;
	}
	return (tmp);
}
