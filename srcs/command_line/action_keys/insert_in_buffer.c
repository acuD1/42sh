/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/11 18:11:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t debug(const char *path, int buff, t_read *in)
{
    int fd;

    if ((fd = open(path, O_WRONLY)) < 0)
        return (-1);
    dprintf(fd,"[%c] {%d}\n", buff, in->x);
    return (1);
}

/*
**	To insert a char in buffer at the end of line
*/

void		insert_char_in_buffer(char buff, t_read *input, int buff_index)
{
	dprintf(STDIN_FILENO, "%c", buff);
	if (buff == NEW_LINE || input->x >= input->ws_col)
	{
		input->x = 0;
		input->y++;
	}
	input->x++;
	input->width++;
	input->buffer[buff_index] = buff;
	input->x_index++;
}

void		insert_at_index(t_read *input, int buff_index, char *buff)
{
	int		j;

	j = ft_strlen(input->buffer) + 1;
	while (--j > buff_index)
		input->buffer[j] = input->buffer[j - 1];
	input->buffer[buff_index] = *buff;
}

/*
**	To insert char in buffer if cursor is inline
**	Termcaps : 	`save_cr' => save cursor position
**			`reset_cr' => restore cursor position
**			`clr_lines' => to clear all following lines from cursor
*/

void		insert_inline_char(char *buff, t_read *input, int buff_index)
{
	char	*tmp;
	int		x;

	x = 0;
	tmp = NULL;
	insert_at_index(input, buff_index, buff);
	tmp = ft_strdup(input->buffer);
	goto_prompt(input);
	ft_strdel(&input->buffer);
	input->buffer = ft_memalloc(BUFF_SIZE);
	insert_str_in_buffer(tmp, input);
	x = buff_index + input->prompt_len;
	while (++x < input->width)
		move_left(buff, input);
	ft_strdel(&tmp);
}

/*
**	To insert a string in buffer at the end of line
*/

void		insert_str_in_buffer(char *d_name, t_read *input)
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
	int		increase_len;

	increase_len = 0;
	buff_index = input->x_index - input->prompt_len;
	if (input->x_index >= BUFF_SIZE)
	{
		increase_len = ft_strlen(input->buffer) + READ_SIZE;
		input->buffer = realloc(input->buffer, increase_len);
	}
	if (ft_strlen(buff) > 1)
	{
		insert_str_in_buffer(buff, input);
		return ;
	}
	else if (input->x_index == input->width)
		insert_char_in_buffer(*buff, input, buff_index);
	else if (input->x_index < input->width)
		insert_inline_char(buff, input, buff_index);
}
