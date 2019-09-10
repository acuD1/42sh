/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/10 14:46:06 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		clr_screen(t_read *line)
{
	int		i;

	i = line->x;
	xtputs(xtgetstr("cl", NULL), 1, my_outc);
	dprintf(STDOUT_FILENO, "%s%s<< %s >>%s ", C_BOLD, C_Y, line->prompt + 1, C_X);
	ft_putstr(line->buffer);
	xtputs(xtgetstr("ho", NULL), 1, my_outc);
	while (--i)
		xtputs(xtgetstr("nd", NULL), 1, my_outc);
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

	xtputs(xtgetstr("up", NULL), 1, my_outc);
	if (line->x < line->prompt_len && line->y == 1)
	{
		while (++(line->x) < line->prompt_len)
			xtputs(xtgetstr("nd", NULL), 1, my_outc);
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
**	CTRL/SHIFT + ARROW_DOWN to move down one line in same column
**	Termcaps capabilities : `do' to move cursor down at beginning of line
**							`nd' to move cursor on the right
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
		xtputs(xtgetstr("do", NULL), 1, my_outc);
		x2 = line->x_index + 1;
		line->x_index = line->x_index * 2 + width;
		if (line->x_index > line->width)
		{
			line->x_index = x2 + width;
			line->x = 0;
		}
		else
			while (--x)
				xtputs(xtgetstr("nd", NULL), 1, my_outc);
		line->y++;
	}
}

void		move_in_column(char *buff, t_read *line)
{
	if (buff[5] == MOVE_UP && line->y != 0)
		move_col_up(line);
	else if (buff[5] == MOVE_DO)
		move_col_down(line);
}

/*
**	(ALT+F | CTRL+F) to jump one word forward
**	(ALT+B | CTRL+B) to jump one word backward
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
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49)
		move_in_column(buff, line);
}
