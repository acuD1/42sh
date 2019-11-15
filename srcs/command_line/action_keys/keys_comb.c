/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/14 16:03:20 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		clr_screen(t_read *line)
{
	int		i;

	i = line->x;
	xtputs(line->tcaps[CLEAR], 1, my_outc);
	dprintf(STDOUT_FILENO, "%s%s%s%s ", C_BOLD, C_Y, line->prompt, C_X);
	ft_putstr(line->buffer);
	xtputs(line->tcaps[UP_LEFT_CORNER], 1, my_outc);
	while (--i)
		xtputs(line->tcaps[KEY_RIGHT], 1, my_outc);
}

/*
**	CTRL/SHIFT + ARROW_UP to move up one line in the same column
**	Termcaps capabilities :	`up' to go up one line in same col
**							`nd' to move the cursor on right
**
*/

void		move_col_up(t_read *line)
{
	int		width;

	xtputs(line->tcaps[KEY_UP], 1, my_outc);
	if (line->x < line->prompt_len && line->y == 1)
	{
		while (++(line->x) < line->prompt_len)
			xtputs(line->tcaps[KEY_RIGHT], 1, my_outc);
		line->x_index = line->x;
	}
	else
	{
		width = get_width_last_line(line) - line->x;
		if (line->y == 1)
			width += line->prompt_len;
		line->x_index = line->x_index - line->x - width + 1;
		line->x++;
	}
	line->y--;
}

/*
**	CTRL/ALT + ARROW_DOWN to move down one line in same column
**	Termcaps capabilities : `down' to move cursor down at beginning of line
**							`right' to move cursor on the right
**
*/

void		move_col_down(t_read *line)
{
	int		width;
	int		nb_ofline;
	int		x;
	int		x2;

	x = line->x;
	width = get_width_current_line(line) - line->x_index;
	nb_ofline = newline_count(line->buffer);
	if (line->y < nb_ofline)
	{
		xtputs(line->tcaps[KEY_DOWN], 1, my_outc);
		x2 = line->x_index + 1;
		line->x_index = line->x_index * 2 + width;
		if (line->x_index > line->width)
		{
			line->x_index = x2 + width;
			line->x = 1;
		}
		else
			while (--x)
				xtputs(line->tcaps[KEY_RIGHT], 1, my_outc);
		line->y++;
	}
}

void		move_in_column(uint64_t value, t_read *line)
{
	if (value & ALT_AW_UP && line->y != 0)
		move_col_up(line);
	else if (value &  ALT_AW_DO)
		move_col_down(line);
}

/*
**	(CTRL+F) to jump one word forward
**	(CTRL+B) to jump one word backward
*/

void			jump_words(char *buff, t_read *line, uint64_t value)
{
	if (value == CTRL_F)
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
	else if (value == CTRL_B)
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
	else if (value == ALT_AW_UP || value == ALT_AW_DO)
		move_in_column(value, line);
}
