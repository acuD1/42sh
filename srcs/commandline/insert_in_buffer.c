/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/11 19:16:47 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/twenty_one.h"

void		insert_char_in_buffer(char buf, t_read *input, int buf_index)
{
	ft_putchar(buf);
	input->x++;
	input->width++;
	input->buffer[buf_index] = buf;
	input->x_index++;
}

void		insert_inline_char(char *buf, t_read *input, int buf_index)
{
	char	*end_line;
	int	rest;
	int 	j;

	j = ft_strlen(input->buffer) + 1;
	rest = input->width - input->x_index;
	while (--j > buf_index)
		input->buffer[j] = input->buffer[j - 1];
	input->buffer[buf_index] = *buf;
	ft_putchar(*buf);
	tputs(tgetstr("sc", NULL), 1, my_outc);
	end_line = ft_strsub(input->buffer, buf_index + 1, rest);
	ft_putstr(end_line);
	tputs(tgetstr("rc", NULL), 1, my_outc);
	input->x++;
	input->x_index++;
	input->width++;
	free(end_line);
}

void		insert_in_buffer(char *buf, t_read *input)
{
	int	buf_index;

	if (input->x >= input->ws_col)
	{
		input->y++;
		input->x = 0;
	}
	buf_index = input->x_index - input->prompt_len;
	if (input->x >= 4096)
		return ;
	if (buf_index == input->width - input->prompt_len)
		insert_char_in_buffer(*buf, input, buf_index);
	else if (buf_index < input->width - input->prompt_len)
		insert_inline_char(buf, input, buf_index);
}
