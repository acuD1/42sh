/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/27 18:03:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			clr_screen(t_read *input)
{
	int		i;

	i = input->x;
	xtputs(input->tcaps[CLEAR], 1, my_outc);
	ft_printf("%s%s%s%s", C_BOLD, C_Y, input->prompt, C_X);
	ft_putstr(input->buffer);
	xtputs(input->tcaps[UP_LEFT_CORNER], 1, my_outc);
	while (i--)
		xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
}

/*
**	CTRL/SHIFT + ARROW_UP to move up one input in the same column
**	Termcaps capabilities :	`up' to go up one input in same col
**				`nd' to move the cursor on right
*/

void			move_col_up(t_read *input)
{
	int		width;

	width = 0;
	xtputs(input->tcaps[KEY_UP], 1, my_outc);
	if (input->x < input->prompt_len && input->y == 1)
	{
		while ((input->x)++ < input->prompt_len)
			xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		input->x_index = input->x;
	}
	else
	{
		width = get_width_last_line(input);
		if (input->y == 1)
			input->x_index = input->x;
		else
			input->x_index -= width;
	}
	input->y--;
}

/*
**	CTRL/ALT + ARROW_DOWN to move down one line at the first column
**	Termcaps capabilities : `down' to move cursor down at beginning of input
*/

void			move_col_down(t_read *input)
{
	int		width;
	int		nb_ofline;

	nb_ofline = 0;
	width = get_width_current_line(input) - input->x;
	if ((nb_ofline = charset_count(input, NEW_LINE, 0)) == 0)
		nb_ofline = input->width / input->ws_col;
	if (input->y < nb_ofline)
	{
		xtputs(input->tcaps[KEY_DOWN], 1, my_outc);
		input->x_index = input->x_index + width + 1;
		input->x = 0;
		input->y++;
	}
}

void			move_in_column(uint64_t value, t_read *input)
{
	if (value == ALT_AW_UP && input->y > 0)
		move_col_up(input);
	else if (value == ALT_AW_DO)
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
		while (input->x_index < input->width
			&& input->buffer[input->x_index - input->prompt_len] == ' ')
			move_right(buff, input);
		while (input->x_index < input->width
			&& input->buffer[input->x_index - input->prompt_len] != ' ')
			move_right(buff, input);
	}
	else if (value == ALT_AW_UP || value == ALT_AW_DO)
		move_in_column(value, input);
}
