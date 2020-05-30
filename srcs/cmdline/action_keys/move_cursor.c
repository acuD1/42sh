/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/28 08:47:29 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	check_tmp_buffer(t_read *term)
{
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	if (term->tmp_buff)
	{
		insert_str_in_buffer(term->tmp_buff, term);
		ft_strdel(&(term->tmp_buff));
		term->history_index = NULL;
	}
}

/*
**		Arrow down print the prev saved in history from history index
*/

void		move_key_down(t_read *term)
{
	t_lst	*w;

	w = NULL;
	if (term->history && term->history_index)
	{
		if (term->history_index && term->history_index->prev)
		{
			w = term->history_index->prev;
			term->history_index = w;
		}
		else
		{
			term->history_index = w;
			check_tmp_buffer(term);
			return ;
		}
		goto_prompt(term);
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE + 1);
		insert_str_in_buffer((char*)w->content, term);
	}
	else
		xtputs(term->tcaps[BELL], 1, my_outc);
}

/*
**		Arrow up print the next saved in history from history index
*/

void		move_key_up(t_read *term)
{
	t_lst	*w;

	if (term->history)
	{
		if (term->history_index && !term->history_index->next)
			return ;
		if (term->history_index && term->history_index->next)
		{
			w = term->history_index->next;
			term->history_index = w;
		}
		else
		{
			if (*term->buffer)
				term->tmp_buff = ft_strdup(term->buffer);
			term->history_index = term->history;
			w = term->history;
		}
		goto_prompt(term);
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE + 1);
		insert_str_in_buffer((char*)w->content, term);
	}
}

/*
**		Arrow right to move the cursor one char on the right
*/

void		move_right(t_read *term)
{
	ssize_t	width;
	ssize_t	buff_index;

	width = get_width_current_line(term);
	buff_index = term->x_index - term->prompt_len;
	if (term->x < width)
	{
		xtputs(term->tcaps[KEY_RIGHT], 1, my_outc);
		term->x_index++;
		term->x++;
	}
	else if (term->buffer[buff_index] == '\n' || term->x == (term->ws_col - 1))
	{
		xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
		xtputs(term->tcaps[KEY_DOWN], 1, my_outc);
		term->x_index++;
		term->x = 0;
		term->y++;
	}
	else if (term->x_index == term->width)
		xtputs(term->tcaps[BELL], 1, my_outc);
}

/*
**		Arrow left to move the cursor one char on the left
*/

void		move_left(t_read *term)
{
	ssize_t	width;

	if ((term->x > term->prompt_len && term->y == 0)
		|| (term->x > 0 && term->y > 0))
	{
		xtputs(term->tcaps[KEY_LEFT], 1, my_outc);
		term->x_index--;
		term->x--;
	}
	else if (term->y > 0 && term->x == 0)
	{
		width = get_width_last_line(term);
		term->x = width;
		while (width--)
			xtputs(term->tcaps[KEY_RIGHT], 1, my_outc);
		xtputs(term->tcaps[KEY_UP], 1, my_outc);
		term->x_index--;
		term->y--;
	}
	else if (term->x_index == term->prompt_len)
		xtputs(term->tcaps[BELL], 1, my_outc);
}
