/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/11 14:53:54 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t debugs(const char *path, t_read *in)
{
    int fd;

    if ((fd = open(path, O_WRONLY)) < 0)
        return (-1);
    dprintf(fd,"y {%d}\n", in->y);
    return (1);
}

void		check_tmp_buffer(t_read *input)
{
	goto_prompt(input);
	ft_strdel(&input->buffer);
	input->buffer = ft_memalloc(BUFF_SIZE);
	if (input->tmp_buff && ft_strlen(input->tmp_buff) > 0)
	{
		insert_str_in_buffer(input->tmp_buff, input);
		ft_strdel(&(input->tmp_buff));
		input->history_index = NULL;
	}
}

/*
**		Arrow down print the prev saved in history from history index
*/

void		move_key_down(t_read *input)
{
	t_lst		*w;

	w = NULL;
	if (input->history && input->history_index)
	{
		if (input->history_index && input->history_index->prev)
		{
			w = input->history_index->prev;
			input->history_index = w;
		}
		else
		{
			check_tmp_buffer(input);
			return ;
		}
		goto_prompt(input);
		ft_strdel(&input->buffer);
		input->buffer = ft_memalloc(BUFF_SIZE);
		insert_str_in_buffer((char*)w->content, input);
	}
}

/*
**		Arrow up print the next saved in history from history index
*/

void		move_key_up(t_read *input)
{
	t_lst		*w;

	if (input->history)
	{
		if (input->history_index && !input->history_index->next)
			return ;
		if (input->history_index && input->history_index->next)
		{
			w = input->history_index->next;
			input->history_index = w;
		}
		else
		{
			if ((*input).buffer)
				input->tmp_buff = ft_strdup(input->buffer);
			input->history_index = input->history;
			w = input->history;
		}
		goto_prompt(input);
		ft_strdel(&input->buffer);
		input->buffer = ft_memalloc(BUFF_SIZE);
		insert_str_in_buffer((char*)w->content, input);
	}
	debugs("/dev/ttys002", input);
}

/*
**		Arrow right to move the cursor one char on the right
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
		xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		input->x_index++;
		input->x++;
	}
	else if (input->x >= input->ws_col - 1 || *buff == NEW_LINE
			|| input->buffer[buff_index] == NEW_LINE)
	{
		xtputs(input->tcaps[LEFT_MARGIN], 1, my_outc);
		xtputs(input->tcaps[KEY_DOWN], 1, my_outc);
		input->x_index++;
		input->x = 0;
		input->y++;
	}
}

/*
**		Arrow left to move the cursor one char on the left
*/

void		move_left(char *buff, t_read *input)
{
	int	width;

	(void)buff;
	if ((input->x > input->prompt_len && input->y == 0)
		|| (input->x > 0 && input->y > 0))
	{
		xtputs(input->tcaps[KEY_LEFT], 1, my_outc);
		input->x_index--;
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		width = get_width_last_line(input);
		input->x = width;
		while (width--)
			xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		xtputs(input->tcaps[KEY_UP], 1, my_outc);
		input->x_index--;
		input->y--;
	}
}
