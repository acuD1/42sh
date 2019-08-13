/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/12 22:42:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Alt + f to jump one word forward
**	Alt + b to jump one word backward
*/

void			jump_words(char *buff, t_read *line)
{
	if (buff[0] == ONE_WORD_LEFT)
	{
		if (line->buffer[line->x_index - line->prompt_len] != ' ')
			move_left(buff, line);
		while (line->x_index > line->prompt_len
			&& line->buffer[line->x_index - line->prompt_len] == ' ')
			move_left(buff, line);
		while (line->x_index > line->prompt_len
			&& line->buffer[line->x_index - line->prompt_len - 1] != ' ')
			move_left(buff, line);
	}
	else if (buff[0] == ONE_WORD_RIGHT)
	{
		if (line->buffer[line->x_index - line->prompt_len] != ' ')
			move_right(buff, line);
		while (line-> x_index < line->width
			&& line->buffer[line->x_index - line->prompt_len] == ' ')
			move_right(buff, line);
		while (line->x_index < line->width
			&& line->buffer[line->x_index - line->prompt_len] != ' ')
			move_right(buff, line);
	}
}

/*
**	Arrow down print the prev saved in history from history index
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
**	Arrow up print the next saved in history from history index
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


uint8_t		get_width_last_line(t_read *input)
{
	int	buf_index;
	int	width;

	width = 0;
	buf_index = input->x_index - input->prompt_len;
	while (--buf_index > 0)
	{
		if (input->buffer[buf_index] == '\n')
		{
			while (buf_index > 0 && input->buffer[--buf_index] != '\n')
				width++;
			break ;
		}
	}
	if (input->y == 1 && input->x == 0)
		width += input->prompt_len - 1;
	return (width);
}

uint8_t		get_width_current_line(t_read *input)
{
	int	buf_index;
	int	width;

	width = 0;
	buf_index = input->x_index - input->prompt_len;
	while (input->buffer[buf_index])
	{
		if (input->buffer[buf_index] == '\n')
			break ;
		width++;
		buf_index++;
	}
	width += input->x;
	return (width);

}

/*
**	Arrow right to move the cursor one char on the right
*/

void		move_right(char *buff, t_read *input)
{
	int	width;
	int	buff_index;

	(void)buff;
	width = get_width_current_line(input);
	buff_index = input->x_index - input->prompt_len;
	if (input->x < width)
	{
		tputs(tgetstr("nd", NULL), 1, my_outc);
		input->x_index++;
		input->x++;
	}
	else if (input->buffer[buff_index] == '\n')
	{
		tputs(tgetstr("cr", NULL), 1, my_outc);
		tputs(tgetstr("do", NULL), 1, my_outc);
		input->x_index++;
		input->x = 0;
		input->y++;
	}
}

/*
**	Arrow left to move the cursor one char on the left
*/

void		move_left(char *buff, t_read *input)
{
	int	width;

	(void)buff;
	if ((input->x > input->prompt_len && input->y == 0)
		|| (input->x != 0 && input->y > 0))
	{
		tputs(tgetstr("le", NULL), 1, my_outc);
		input->x_index--;
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		width = get_width_last_line(input);
		input->x = width;
		while (width--)
			tputs(tgetstr("nd", NULL), 1, my_outc);
		tputs(tgetstr("up", NULL), 1, my_outc);
		input->x_index--;
		input->y--;
	}
}
