/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:13:27 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/04 12:35:36 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

void		remove_newline(t_read *line)
{
	char	*tmp;
	int	i;
	int	j;

	i = -1;
	j = -1;
	tmp = ft_strdup(line->buffer);
	ft_bzero(line->buffer, line->width);
	while (tmp[++i])
	{
		if (tmp[i] == NEW_LINE)
			line->width--;
		else
			line->buffer[++j] = tmp[i];
	}
	line->buffer[j + 1] = '\0';
	ft_strdel(&tmp);
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
	int		buff_index;
	int		width;
	int		x;

	width = 0;
	x = input->x;
	buff_index = input->x_index - input->prompt_len;
	while (input->buffer[buff_index])
	{
		if (input->buffer[buff_index] == NEW_LINE || x == input->ws_col)
			break ;
		width++;
		x++;
		buff_index++;
	}
	width += input->x;
	return (width);
}
