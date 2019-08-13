/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/13 01:24:09 by fcatusse         ###   ########.fr       */
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
	{
		input->x = 0;
		input->y++;
	}
	else
		input->x++;
	input->width++;
	input->buffer[buff_index] = buff;
	input->x_index++;
	if (input->x == input->ws_col)
	{
		/* move_right(&buff, input); */
		/* input->x_index--; */
		insert_newline_in_buff(input);
	}
}

/*
**	To insert char in buffer if cursor is inline
*/

void		insert_inline_char(char *buff, t_read *input, int buff_index)
{
	int 	j;
	int	x;
	int	x_index;

	j = ft_strlen(input->buffer) + input->y + 1;
	while (--j > buff_index)
	{
		if (input->buffer[j - 1] == '\n')
		{
			input->buffer[j] = input->buffer[j - 2];
			j = j - 2;
		}
		input->buffer[j] = input->buffer[j - 1];
	}
	input->buffer[buff_index] = *buff;
	tputs(tgetstr("sc", NULL), 1, my_outc);
	j = input->width;
	x = input->x;
	x_index = input->x_index;
	goto_prompt(input);
	input->width = j++;
	input->x = x;
	input->x_index = x_index;
	ft_putstr(input->buffer);
	tputs(tgetstr("rc", NULL), 1, my_outc);
	move_right(buff, input);

	/* ft_putchar(*buff); */
	/* j = -1; */
	/* end_line = ft_strsub(input->buffer, buff_index + 1, rest); */
	/* while (end_line[++j]) */
	/* { */
	/* 	ft_putchar(end_line[j]); */
	/* } */
	//free(end_line);
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
