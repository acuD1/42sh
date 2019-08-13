/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/13 19:34:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

uint8_t		get_width_last_line(t_read *input)
{
	int		buff_index;
	int		width;

	width = 0;
	buff_index = input->x_index - input->prompt_len;
	while (buff_index-- > 0)
	{
		if (input->buffer[buff_index] == NEW_LINE)
		{
			while (buff_index > 0 && input->buffer[--buff_index] != NEW_LINE)
				width++;
			break ;
		}
	}
	if (input->y == 1 && input->x == 0)
		width += input->prompt_len - 1;
	return (width);
}

uint8_t		get_width_current_line(t_read *input)
{
	int		buf_index;
	int		width;

	width = 0;
	buf_index = input->x_index - input->prompt_len;
	while (input->buffer[buf_index])
	{
		if (input->buffer[buf_index] == NEW_LINE)
			break ;
		width++;
		buf_index++;
	}
	width += input->x;
	return (width);
}
