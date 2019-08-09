/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/09 16:24:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	To insert a char in buffer at the end of line
*/

void		insert_char_in_buffer(char buff, t_read *input, int buff_index)
{
	ft_putchar(buff);
	if (buff == '\n')
		input->y++;
	input->x++;
	input->width++;
	input->buffer[buff_index] = buff;
	input->x_index++;
	if (input->x == input->ws_col)
	{
		move_right(&buff, input);
		input->x_index--;
	}
}

/*
**	To insert char in buffer if cursor is inline
*/

void		insert_inline_char(char *buff, t_read *input, int buff_index)
{
	char	*end_line;
	int	rest;
	int 	j;

	j = ft_strlen(input->buffer) + 1;
	rest = input->width - input->x_index;
	while (--j > buff_index)
		input->buffer[j] = input->buffer[j - 1];
	input->buffer[buff_index] = *buff;
	ft_putchar(*buff);
	tputs(tgetstr("sc", NULL), 1, my_outc);
	end_line = ft_strsub(input->buffer, buff_index + 1, rest);
	ft_putstr(end_line);
	tputs(tgetstr("rc", NULL), 1, my_outc);
	input->x++;
	input->x_index++;
	input->width++;
	free(end_line);
	if (input->x == input->ws_col)
	{
		move_right(buff, input);
		input->x_index--;
	}
}

/*
**	To insert a string in buffer at the end of line
*/

void			insert_str_in_buffer(char *d_name, t_read *input)
{
	int		buff_index;

	buff_index = input->x_index - input->prompt_len;
	while (*d_name)
	{
		if (buff_index < input->width - input->prompt_len)
			insert_inline_char(d_name, input, buff_index);
		else
			insert_char_in_buffer(*d_name, input, buff_index);
		d_name++;
		buff_index++;
	}
}

/*
**	Insert one char if size of buff is equal to 1
**	Otherwise (size greater than 1) paste the string in buffer
**	If cursor position is under the width of line => insert inline
*/

void		insert_in_buffer(char *buff, t_read *input)
{
	int	buff_index;

	if (input->x >= input->ws_col)
	{
		input->y++;
		input->x = 0;
	}
	buff_index = input->x_index - input->prompt_len;
	if (input->x >= BUFF_SIZE)
		return ;
	if (ft_strlen(buff) > 1)
	{
		insert_str_in_buffer(buff, input);
		ft_bzero(buff, READ_SIZE);
		return ;
	}
	else if (buff_index == input->width - input->prompt_len)
		insert_char_in_buffer(*buff, input, buff_index);
	else if (buff_index < input->width - input->prompt_len)
		insert_inline_char(buff, input, buff_index);
}
