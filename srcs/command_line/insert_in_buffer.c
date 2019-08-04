/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/04 21:53:37 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		paste_board(char *buf, t_read *input, int buf_index)
{
	int		i;

	i = -1;
	while (buf[++i])
		insert_char_in_buffer(buf[i], input, buf_index);
}

/*
** To insert a string in buffer at the end of line
*/
void			insert_str_in_buffer(char *d_name, t_read *input)
{
	int		i;
	int		buf_index;

	i = -1;
	buf_index = input->x_index - input->prompt_len;
	while (d_name[++i])
	{
		insert_char_in_buffer(d_name[i], input, buf_index);
		buf_index++;
	}
}

/*
** To insert a char in buffer at the end of line
*/
void		insert_char_in_buffer(char buf, t_read *input, int buf_index)
{
	ft_putchar(buf);
	input->x++;
	input->width++;
	input->buffer[buf_index] = buf;
	input->x_index++;
	if (input->x == input->ws_col)
	{
		move_right(&buf, input);
		input->x_index--;
	}
}

/*
** To insert char in buffer if cursor is inline
*/
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
	if (input->x == input->ws_col)
	{
		move_right(buf, input);
		input->x_index--;
	}
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
	if (input->x >= BUFF_SIZE)
		return ;
	/* if (ft_strlen(buf) > 1) */
	/* { */
	/* 	paste_board(buf, input, buf_index); */
	/* 	return ; */
	/* } */
	else if (buf_index == input->width - input->prompt_len)
		insert_char_in_buffer(*buf, input, buf_index);
	else if (buf_index < input->width - input->prompt_len)
		insert_inline_char(buf, input, buf_index);
}
