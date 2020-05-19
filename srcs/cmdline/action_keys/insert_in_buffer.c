/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/19 15:09:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

/*
**		To insert a char in buffer at the end of line
**		If the cursor is equal to the last column of the screen :
**		- Newline is inserted in the buffer and coordinates are updated
**		- Buff is displayed at x = 0
**		Otherwise it is not inserted again if buff is already a newline
*/

void		insert_char_in_buffer
	(const char buff, t_read *term, ssize_t buff_index)
{
	if (buff == '\n')
	{
		term->x = -1;
		term->y++;
	}
	write(STDOUT_FILENO, &buff, 1);
	term->x++;
	term->width++;
	term->buffer[buff_index] = buff;
	term->x_index++;
	if (term->x == term->ws_col)
	{
		term->x = 0;
		term->y++;
		xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
		xtputs(term->tcaps[KEY_DOWN], 1, my_outc);
	}
}

static void	insert_at_index(t_read *term, ssize_t buff_index, const char *buff)
{
	ssize_t	j;

	j = (ssize_t)ft_strlen(term->buffer) + 1;
	while (--j > buff_index)
		term->buffer[j] = term->buffer[j - 1];
	term->buffer[buff_index] = *buff;
}

/*
**		To insert char in buffer if cursor is inline
**		Termcaps : 	`save_cr' => save cursor position
**					`reset_cr' => restore cursor position
**					`clr_lines' => to clear all following lines from cursor
*/

static void	insert_inline_char
	(const char *buff, t_read *term, ssize_t buff_index)
{
	char	*tmp;
	ssize_t	x;

	x = 0;
	tmp = NULL;
	insert_at_index(term, buff_index, buff);
	tmp = ft_strdup(term->buffer);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(tmp, term);
	x = buff_index + (ssize_t)term->prompt_len;
	while (++x < term->width)
		move_left(term);
	ft_strdel(&tmp);
}

/*
**		To insert a string in buffer at the end of line
*/

void		insert_str_in_buffer(const char *d_name, t_read *term)
{
	ssize_t	buff_index;
	size_t	i;

	i = ft_strlen(d_name);
	if (i >= BUFF_SIZE)
		term->buffer = ft_realloc(term->buffer, BUFF_SIZE + i);
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
**		Insert one char if size of buff is equal to 1
**		Otherwise (size greater than 1) paste the string in buffer
**		If cursor position is under the width of line => insert inline
*/

void		insert_in_buffer(const char *buff, t_read *term)
{
	ssize_t	buff_index;
	ssize_t	len;
	ssize_t	increase_len;

	increase_len = 0;
	buff_index = term->x_index - term->prompt_len;
	len = (*buff) ? (ssize_t)ft_strlen(buff) : 0;
	if (term->x_index >= BUFF_SIZE || term->x_index + len >= BUFF_SIZE)
	{
		increase_len = (ssize_t)ft_strlen(term->buffer) + READ_SIZE;
		term->buffer = ft_realloc(term->buffer, (size_t)increase_len);
	}
	if (len > 1)
	{
		insert_str_in_buffer(buff, term);
		return ;
	}
	else if (term->x_index == term->width)
		insert_char_in_buffer(*buff, term, buff_index);
	else if (term->x_index < term->width)
		insert_inline_char(buff, term, buff_index);
}
