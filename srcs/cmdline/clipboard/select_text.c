/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:33:55 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/09 10:28:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		select_on_left(t_read *term, t_cmd *copy)
{
	ssize_t		x;

	move_left(term);
	x = term->x_index - term->prompt_len;
	if (x <= copy->first && x <= copy->last)
	{
		xtputs(term->tcaps[SELECT_ON], 1, my_outc);
		if (copy->first > 0)
			copy->first -= 1;
	}
	else
		copy->last -= 1;
	write(STDOUT_FILENO, &term->buffer[x], 1);
	xtputs(term->tcaps[SELECT_OFF], 1, my_outc);
	if (term->x != (term->ws_col - 1))
	{
		term->x += 1;
		term->x_index += 1;
		move_left(term);
	}
}

static void		select_on_right(t_read *term, t_cmd *copy)
{
	ssize_t		x;

	x = term->x_index - term->prompt_len;
	if (x >= copy->first && x >= copy->last)
	{
		xtputs(term->tcaps[SELECT_ON], 1, my_outc);
		copy->last += 1;
	}
	else
		copy->first += 1;
	write(STDOUT_FILENO, &term->buffer[x], 1);
	xtputs(term->tcaps[SELECT_OFF], 1, my_outc);
	term->x += 1;
	term->x_index += 1;
}

static void		deselect_all(t_read *term)
{
	ssize_t		pos;
	ssize_t		len;
	char		*tmp;

	pos = term->width - term->x_index;
	len = (ssize_t)ft_strlen(term->buffer);
	tmp = ft_strdup(term->buffer);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(tmp, term);
	while (pos--)
		move_left(term);
	ft_strdel(&tmp);
}

static t_cmd	ak_selection(t_read *term, u_int64_t value, t_cmd copy)
{
	if (value == SELECT_RIGHT && term->x_index < term->width)
		select_on_right(term, &copy);
	else if (value == SELECT_LEFT
		&& term->x >= (term->prompt_len * (term->y == 0 ? 1 : 0)))
		select_on_left(term, &copy);
	else if (value == CTRL_K)
		copy_text(term, copy);
	else if (value == CTRL_P)
		paste_text(term);
	else if (value == CTRL_X)
		cut_text(term, copy);
	else if (value != SELECT_LEFT && value != SELECT_RIGHT)
	{
		deselect_all(term);
		copy.first = 0;
		copy.last = 0;
	}
	return (copy);
}

void			load_selection(t_read *term, const char *buff, u_int64_t value)
{
	ssize_t		x;
	t_cmd		copy;

	x = term->x_index - term->prompt_len;
	ft_bzero(&copy, sizeof(t_cmd));
	copy.first = (int32_t)x;
	copy.last = (int32_t)x;
	if (value == SELECT_LEFT)
		select_on_left(term, &copy);
	else if (value == SELECT_RIGHT)
		select_on_right(term, &copy);
	ft_bzero((void *)buff, READ_SIZE + 1);
	while (read(STDIN_FILENO, (char*)buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		copy = ak_selection(term, value, copy);
		if (copy.first == 0 && copy.last == 0)
			break ;
		ft_bzero((void *)buff, READ_SIZE + 1);
	}
}
