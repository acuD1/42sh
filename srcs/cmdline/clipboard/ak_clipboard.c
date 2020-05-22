/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:04:09 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 15:03:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**				CTRL_X ACTION KEY => CUT SELECTED STRING
**		copy_text => copies current string selected in t_read structure
**		del_key   => deletes the string copied in the current line and in buffer
*/

void		cut_text(t_read *term, t_cmd copy)
{
	ssize_t		cpy_len;

	copy_text(term, copy);
	cpy_len = (ssize_t)ft_strlen(term->cpy);
	while (cpy_len--)
		del_key(term);
}

/*
**				CTRL_P ACTION KEY => PASTE SELECTED STRING
**		insert the last string copied at specified index in the buffer and line
*/

void		paste_text(t_read *term)
{
	ssize_t		len_cpy;
	ssize_t		buffer_len;

	buffer_len = (ssize_t)ft_strlen(term->buffer);
	len_cpy = (ssize_t)ft_strlen(term->cpy);
	if (buffer_len + len_cpy >= BUFF_SIZE)
		term->buffer = ft_realloc(term->buffer, (size_t)(buffer_len + len_cpy));
	if (term->cpy)
		insert_str_in_buffer(term->cpy, term);
}

/*
**				CTRL_K ACTION KEY => SELECTED STRING COPY
**		Copy string from the first character selected to the last selected
**		If first and last are equals to 0 the function copies 1 character only
**		from the current cursor position
*/

void		copy_text(t_read *term, t_cmd copy)
{
	ft_strdel(&term->cpy);
	if (copy.first == 0 && copy.last == 0)
	{
		copy.first = (int32_t)(term->x_index - term->prompt_len);
		copy.last = copy.first + 1;
	}
	term->cpy = ft_strsub(term->buffer,
					(unsigned int)copy.first, (size_t)(copy.last - copy.first));
}

/*
**						ACTIONS KEYS CLIPBOARD
**		SELECT		=> launch selection mode to select all or part of a line
**		AK_SELECT	=> CTRL + SHIFT + ARROW (LEFT/RIGHT)
**					===================================
**		CTRL_K		=> copy text selected from keyboard
**		CTRL_P		=> paste text copied from clipboard
**		CTRL_X		=> cut and copy text selected
*/

void		ak_clipboard(t_read *term, const char *buff, u_int64_t *value)
{
	t_cmd		copy;

	if ((*value != CTRL_P && !*term->buffer) || ft_strchr(term->buffer, '\n'))
		return ;
	if (*value == SELECT_RIGHT && term->x_index < term->width)
		load_selection(term, buff, *value);
	else if (*value == SELECT_LEFT
	&& term->x >= (term->prompt_len * (term->y == 0 ? 1 : 0)))
		load_selection(term, buff, *value);
	else if (*value == CTRL_K)
	{
		ft_bzero(&copy, sizeof(t_cmd));
		copy_text(term, copy);
	}
	else if (*value == CTRL_P)
		paste_text(term);
	else if (*value == CTRL_X)
	{
		ft_bzero(&copy, sizeof(t_cmd));
		cut_text(term, copy);
	}
	*value = get_mask(buff);
}
