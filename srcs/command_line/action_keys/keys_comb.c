/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/25 14:51:33 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		clr_screen(t_read *input)
{
	int		i;

	i = input->x;
	xtputs(input->tcaps[CLEAR], 1, my_outc);
	ft_dprintf(STDOUT_FILENO, "%s%s%s$ %s", C_BOLD, C_Y, input->prompt, C_X);
	ft_putstr(input->buffer);
	xtputs(input->tcaps[UP_LEFT_CORNER], 1, my_outc);
	while (i--)
		xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
}

/*
**	CTRL/SHIFT + ARROW_UP to move up one input in the same column
**	Termcaps capabilities :	`up' to go up one input in same col
**							`nd' to move the cursor on right
**
*/

void		move_col_up(t_read *input)
{
	int		width;

	xtputs(input->tcaps[KEY_UP], 1, my_outc);
	if (input->x < input->prompt_len && input->y == 1)
	{
		while (++(input->x) < input->prompt_len)
			xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		input->x_index = input->x;
	}
	else
	{
		width = get_width_last_line(input) - input->x;
		if (input->y == 1)
			width += input->prompt_len;
		input->x_index = input->x_index - input->x - width + 1;
		input->x++;
	}
	input->y--;
}

/*
**	CTRL/ALT + ARROW_DOWN to move down one input in same column
**	Termcaps capabilities : `down' to move cursor down at beginning of input
**							`right' to move cursor on the right
**
*/

void		move_col_down(t_read *input)
{
	int		width;
	int		nb_ofline;
	int		x;
	int		x2;

	width = get_width_current_line(input) - input->x_index;
	x2 = input->x_index - input->prompt_len;
	if ((nb_ofline = charset_count(input, NEW_LINE, x2)) == 0)
		nb_ofline = input->width / input->ws_col;
	x = input->x;
	if (input->y < nb_ofline)
	{
		xtputs(input->tcaps[KEY_DOWN], 1, my_outc);
		x2 = input->x_index + 1;
		input->x_index = input->x_index * 2 + width;
		if (input->x_index > input->width)
		{
			input->x_index = x2 + width;
			input->x = 1;
		}
		else
			while (--x)
				xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		input->y++;
	}
}

void		move_in_column(uint64_t value, t_read *input)
{
	if (value & ALT_AW_UP && input->y != 0)
		move_col_up(input);
	else if (value &  ALT_AW_DO)
		move_col_down(input);
}

/*
**	(CTRL+F) to jump one word forward
**	(CTRL+B) to jump one word backward
*/

void			jump_words(char *buff, t_read *input, uint64_t value)
{
	if (value == CTRL_F)
	{
		if (input->buffer[input->x_index - input->prompt_len] != ' ')
			move_left(buff, input);
		while (input->x_index > input->prompt_len
			&& input->buffer[input->x_index - input->prompt_len] == ' ')
			move_left(buff, input);
		while (input->x_index > input->prompt_len
			&& input->buffer[input->x_index - input->prompt_len - 1] != ' ')
			move_left(buff, input);
	}
	else if (value == CTRL_B)
	{
		if (input->buffer[input->x_index - input->prompt_len] != ' ')
			move_right(buff, input);
		while (input-> x_index < input->width
			&& input->buffer[input->x_index - input->prompt_len] == ' ')
			move_right(buff, input);
		while (input->x_index < input->width
			&& input->buffer[input->x_index - input->prompt_len] != ' ')
			move_right(buff, input);
	}
	else if (value == ALT_AW_UP || value == ALT_AW_DO)
		move_in_column(value, input);
}
