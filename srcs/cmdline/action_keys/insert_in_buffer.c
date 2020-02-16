/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/15 15:33:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	To insert a char in buffer at the end of line
*/

void		insert_char_in_buffer(const char buff, t_read *term, int buff_index)
{
	ft_dprintf(STDIN_FILENO, "%c", buff);
	if (buff == NEW_LINE[0] || term->x >= term->ws_col)
	{
		if (buff == NEW_LINE[0])
			term->x = -1;
		else
			term->x = 0;
		term->y++;
	}
	term->x++;
	term->width++;
	term->buffer[buff_index] = buff;
	term->x_index++;
}

static void	insert_at_index(t_read *term, int buff_index, const char *buff)
{
	int		j;

	j = ft_strlen(term->buffer) + 1;
	while (--j > buff_index)
		term->buffer[j] = term->buffer[j - 1];
	term->buffer[buff_index] = *buff;
}

/*
**	To insert char in buffer if cursor is inline
**	Termcaps : 	`save_cr' => save cursor position
**			`reset_cr' => restore cursor position
**			`clr_lines' => to clear all following lines from cursor
*/

static void	insert_inline_char(const char *buff, t_read *term, int buff_index)
{
	char	*tmp;
	int		x;

	x = 0;
	tmp = NULL;
	insert_at_index(term, buff_index, buff);
	tmp = ft_strdup(term->buffer);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE);
	insert_str_in_buffer(tmp, term);
	x = buff_index + term->prompt_len;
	while (++x < term->width)
		move_left(buff, term);
	ft_strdel(&tmp);
}

/*
**	To insert a string in buffer at the end of line
*/

void		insert_str_in_buffer(const char *d_name, t_read *term)
{
	int		buff_index;
	int		i;

	i = ft_strlen(d_name);
	while (i--)
	{
		buff_index = term->x_index - term->prompt_len;
		if (term->x_index < term->width)
			insert_inline_char(d_name, term, buff_index);
		else
			insert_char_in_buffer(*d_name, term, buff_index);
		d_name++;
	}
}

/*
**	Insert one char if size of buff is equal to 1
**	Otherwise (size greater than 1) paste the string in buffer
**	If cursor position is under the width of line => insert inline
*/

void		insert_in_buffer(const char *buff, t_read *term)
{
	int		buff_index;
	int		increase_len;

	increase_len = 0;
	buff_index = term->x_index - term->prompt_len;
	if (term->x_index >= BUFF_SIZE)
	{
		increase_len = ft_strlen(term->buffer) + READ_SIZE;
		term->buffer = realloc(term->buffer, increase_len);
	}
	if (ft_strlen(buff) > 1)
	{
		insert_str_in_buffer(buff, term);
		return ;
	}
	else if (term->x_index == term->width)
		insert_char_in_buffer(*buff, term, buff_index);
	else if (term->x_index < term->width)
		insert_inline_char(buff, term, buff_index);
}
