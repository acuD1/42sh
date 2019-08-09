/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/09 16:17:47 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Alt + f to jump one word forward
** Alt + b to jump one word backward
** To Do: (*f) / infinite loop multiline
*/

void			jump_words(char *buff, t_read *line)
{
	int		last_char;

	last_char = line->x_index - line->prompt_len;
	if (buff[0] == ONE_WORD_LEFT)
	{
		if (line->buffer[last_char] != ' ')
			move_left(buff, line);
		while (line->x > line->prompt_len && line->buffer[last_char] == ' ')
			move_left(buff, line);
		while (line->x > line->prompt_len && line->buffer[last_char - 1] != ' ')
			move_left(buff, line);
	}
	else if (buff[0] == ONE_WORD_RIGHT)
	{
		if (line->buffer[last_char] != ' ')
			move_right(buff, line);
		while (line-> x < line->width && line->buffer[last_char] == ' ')
			move_right(buff, line);
		while (line->x < line->width && line->buffer[last_char] != ' ')
			move_right(buff, line);
	}
}

/*
** Arrow down print the prev saved in history from history index
*/
void			move_key_down(t_read *line)
{
	t_lst	 	*w;
	int		i;

	i = -1;
	if (line->history)
	{
		goto_prompt(line);
		memset(line->buffer, 0, strlen(line->buffer));
		if (line->history_index && line->history_index->prev)
		{
			w = line->history_index->prev;
			line->history_index = w;
		}
		else
		{
			line->history_index = line->history->prev;
			return ;
		}
		while (w->data && w->data[++i])
			insert_char_in_buffer(w->data[i], line, i);
	}
}

/*
** Arrow up print the next saved in history from history index
*/

void			move_key_up(t_read *line)
{
	t_lst	 	*w;
	int		i;

	i = -1;
	if (line->history)
	{
		if (line->history_index && !line->history_index->next)
			return ;
		if (line->history_index && line->history_index->next)
		{
			w = line->history_index->next;
			line->history_index = w;
		}
		else
		{
			line->history_index = line->history;
			w = line->history;
		}
		goto_prompt(line);
		memset(line->buffer, 0, strlen(line->buffer));
		while (w->data && w->data[++i])
			insert_char_in_buffer(w->data[i], line, i);
	}
}

/*
** Arrow right to move the cursor one char on the right
*/

void		move_right(char *buff, t_read *input)
{
	(void)buff;
	if (input->x < input->ws_col - 1 && input->x + (input->ws_col * input->y) < input->width)
	{
		tputs(tgetstr("nd", NULL), 1, my_outc);
		input->x_index++;
		input->x++;
	}
	else if (input->x >= input->ws_col - 1)
	{
		tputs(tgetstr("cr", NULL), 1, my_outc);
		tputs(tgetstr("do", NULL), 1, my_outc);
		input->x_index++;
		input->x = 0;
		input->y++;
	}
}

/*
** Arrow left to move the cursor one char on the left
*/

void		move_left(char *buff, t_read *input)
{
	int	i;

	(void)buff;
	i = input->width;
	if (input->x != 0 && (input->x > (input->prompt_len * (input->y == 0 ? 1 : 0))))
	{
		tputs(tgetstr("le", NULL), 1, my_outc);
		input->x_index--;
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		while (i--)
			tputs(tgetstr("nd", NULL), 1, my_outc);
		tputs(tgetstr("up", NULL), 1, my_outc);
		input->x_index--;
		input->y--;
		input->x = input->ws_col - 1;
	}
}
