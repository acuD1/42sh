/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/24 16:40:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/ioctl.h>
# include "../../inc/twenty_one.h"

/*
** Alt + f to jump one word forward
** Alt + b to jump one word backward
*/

void			jump_words(char *buf, t_read *line)
{
	if (buf[0] == 6)
	{
		if (line->buffer[line->x - line->prompt_len] != ' ')
			move_left(buf, line);
		while (line->x > line->prompt_len &&
			line->buffer[line->x - line->prompt_len] == ' ')
			move_left(buf, line);
		while (line->x > line->prompt_len &&
			line->buffer[line->x - line->prompt_len - 1] != ' ')
			move_left(buf, line);
	}
	else if (buf[0] == 2)
	{
		if (line->buffer[line->x - line->prompt_len] != ' ')
			move_right(buf, line);
		while (line-> x < line->width &&
			line->buffer[line->x - line->prompt_len] == ' ')
			move_right(buf, line);
		while (line->x < line->width &&
			line->buffer[line->x - line->prompt_len] != ' ')
			move_right(buf, line);
	}
}

void			move_key_down(t_read *line)
{
	t_history 	*w;
	int		i;

	i = -1;
	if (line->history)
	{
		goto_prompt(line);
		if (line->history_index && line->history_index->prev)
		{
			w = line->history_index->prev;
			line->history_index = w;
		}
		else
		{
			line->history_index = line->history;
			w = line->history;
		}
		memset(line->buffer, 0, strlen(line->buffer));
		while (w->data && w->data[++i])
			insert_char_in_buffer(w->data[i], line, i);
	}
}

void			move_key_up(t_read *line)
{
	t_history 	*w;
	int		i;

	i = -1;
	if (line->history)
	{
		if (line->history_index && !line->history_index->next)
			return;
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

void		move_right(char *buf, t_read *input)
{
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

void		move_left(char *buf, t_read *input)
{
	int	i;

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
