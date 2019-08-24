/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/23 14:17:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

uint8_t		to_next_newline(char *buffer, int buff_index)
{
	int	width;

	width = 0;
	while (buffer[buff_index--])
	{
		if (buffer[buff_index] == '\n')
			return (width);
		width++;
	}
	return (width);
}

uint8_t		get_width_last_line(t_read *input)
{
	int	buff_index;
	int	width;
	int	x;

	width = 0;
	x = input->x;
	buff_index = input->x_index - input->prompt_len;
	while (buff_index-- > 0)
	{
		if (x == 0)
		{
			width = to_next_newline(input->buffer, buff_index);
				break ;
		}
		x--;
	}
	if (input->y == 1 && input->x == 0 && width != input->ws_col)
	{
		input->x = width + input->prompt_len - 1;
		width += input->prompt_len - 2;
	}
	return (width);
}

uint8_t		get_width_current_line(t_read *input)
{
	int		buf_index;
	int		width;
	int		x;

	width = 0;
	x = input->x;
	buf_index = input->x_index - input->prompt_len;
	while (input->buffer[buf_index])
	{
		if (input->buffer[buf_index] == NEW_LINE || x == input->ws_col)
			break ;
		width++;
		x++;
		buf_index++;
	}
	width += input->x;
	return (width);
}
