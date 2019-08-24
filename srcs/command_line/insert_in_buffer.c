/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/24 16:49:52 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		test(t_read *test)
{
	size_t		i = -1;

	while (i++ <= ft_strlen(test->buffer))
		printf("[%zu] => %c\n", i, test->buffer[i]);
}

/*
**	To insert a char in buffer at the end of line
*/

void		insert_char_in_buffer(char buff, t_read *input, int buff_index)
{
	if ((input->new_line == 0 && buff != NEW_LINE) || input->new_line == 1)
		ft_putchar(buff);
	if (buff == NEW_LINE)
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
		move_right("\n", input);
		input->x_index--;
		input->y--;
		insert_newline_in_buff(input);
	}
}

/*
**	To insert char in buffer if cursor is inline
**	Termcaps `sc' => save cursor position
**		 `rc' => restore cursor position
*/

void		insert_inline_char(char *buff, t_read *input, int buff_index)
{
	int 	j;
	int	x;
	int	w;
	int	y;

	j = ft_strlen(input->buffer) + 1;
	while (--j > buff_index)
	{
		if (input->buffer[j - 1] == NEW_LINE)
		{
			input->buffer[j] = input->buffer[j - 2];
			j = j - 2;
		}
		input->buffer[j] = input->buffer[j - 1];
	}
	input->buffer[buff_index] = *buff;
	move_right(buff, input);
	tputs(tgetstr("sc", NULL), 1, my_outc);
	j = input->x;
	x = input->x_index;
	w = input->width;
	y = input->y;
	goto_prompt(input);
	ft_putstr(input->buffer);
	input->x = j;
	input->x_index = x;
	input->width = w + 1;
	input->y = y;
	tputs(tgetstr("rc", NULL), 1, my_outc);
}

/*
**	To insert a string in buffer at the end of line
*/

void			insert_str_in_buffer(char *d_name, t_read *input)
{
	int		buff_index;
	int		i;

	i = ft_strlen(d_name);
	while (i--)
	{
		buff_index = input->x_index - input->prompt_len;
		if (input->x_index < input->width)
			insert_inline_char(d_name, input, buff_index);
		else
			insert_char_in_buffer(*d_name, input, buff_index);
		d_name++;
	}
}

/*
**	Insert one char if size of buff is equal to 1
**	Otherwise (size greater than 1) paste the string in buffer
**	If cursor position is under the width of line => insert inline
*/

void		insert_in_buffer(char *buff, t_read *input)
{
	int		buff_index;

	buff_index = input->x_index - input->prompt_len;
	if (input->x >= BUFF_SIZE)
		return ;
	if (ft_strlen(buff) > 1)
	{
		insert_str_in_buffer(buff, input);
		ft_bzero(buff, READ_SIZE);
		return ;
	}
	else if (input->x_index == input->width)
		insert_char_in_buffer(*buff, input, buff_index);
	else if (input->x_index < input->width)
		insert_inline_char(buff, input, buff_index);
}
