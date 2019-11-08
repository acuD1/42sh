/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/08 21:10:08 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	To insert a char in buffer at the end of line
*/

void		insert_char_in_buffer(char buff, t_read *input, int buff_index)
{
	if (input->x != 0 || (input->x == 0 && buff != NEW_LINE))
		ft_dprintf(STDIN_FILENO, "%c", buff);
	if (buff == NEW_LINE || input->x > input->ws_col)
	{
		//	(input->x == 0) ? input->y-- : 0;
		input->x = 0;
		input->y++;
	}
	else
		input->x++;
	input->width++;
	input->buffer[buff_index] = buff;
	input->x_index++;
	//	move_right(&buff, input);
	/* if (input->x >= input->ws_col) */
	/* 	insert_newline_in_buff(input); */
}

/*
**	To insert char in buffer if cursor is inline
**	Termcaps : 	`save_cr' => save cursor position
**			`reset_cr' => restore cursor position
**			`clr_lines' => to clear all following lines from cursor
*/

void		insert_inline_char(char *buff, t_read *input, int buff_index)
{
	int 	j;
	int	i;
	char	*tmp;

	tmp = NULL;
	input->width += 1;
	j = ft_strlen(input->buffer) + 1;
	i = input->width - input->prompt_len;
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
	tmp = ft_strsub(input->buffer, buff_index, strlen_to(input->buffer, '\0'));
	xtputs(input->tcaps[SAVE_CR], 1, my_outc);
	xtputs(input->tcaps[CLR_LINES], 1, my_outc);
	ft_dprintf(STDOUT_FILENO, "%s", tmp);
	xtputs(input->tcaps[RESTORE_CR], 1, my_outc);
	move_right(buff, input);
	ft_strdel(&tmp);

	win_size("/dev/ttys001", input->width, input->width % input->ws_col);
//	win_size("/dev/ttys002", input->y_li, input->ws_li);
	if (input->y_li == input->ws_li && input->width % input->ws_col == 2)
		xtputs(input->tcaps[KEY_UP], 1, my_outc);
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
	if (input->x_index >= BUFF_SIZE)
		input->buffer = realloc(input->buffer, ft_strlen(input->buffer) + 1);
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
