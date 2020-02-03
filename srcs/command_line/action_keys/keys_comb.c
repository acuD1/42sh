/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 17:10:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		clr_screen(t_read *term)
{
	int		i;

	i = term->x;
	xtputs(term->tcaps[CLEAR], 1, my_outc);
	ft_printf("%s%s%s%s", C_BOLD, C_Y, term->prompt, C_X);
	ft_putstr(term->buffer);
	xtputs(term->tcaps[UP_LEFT_CORNER], 1, my_outc);
	while (i--)
		xtputs(term->tcaps[KEY_RIGHT], 1, my_outc);
}

/*
**	CTRL/SHIFT + ARROW_UP to move up one input in the same column
**	Termcaps capabilities :	`up' to go up one input in same col
**				`nd' to move the cursor on right
*/

static void	move_col_up(t_read *term)
{
	int		width;

	width = 0;
	xtputs(term->tcaps[KEY_UP], 1, my_outc);
	if (term->x < term->prompt_len && term->y == 1)
	{
		while ((term->x)++ < term->prompt_len)
			xtputs(term->tcaps[KEY_RIGHT], 1, my_outc);
		term->x_index = term->x;
	}
	else
	{
		width = get_width_last_line(term);
		if (term->y == 1)
			term->x_index = term->x;
		else
			term->x_index -= width;
	}
	term->y--;
}

/*
**	CTRL/ALT + ARROW_DOWN to move down one line at the first column
**	Termcaps capabilities : `down' to move cursor down at beginning of input
*/

static void	move_col_down(t_read *term)
{
	int		width;
	int		nb_ofline;

	nb_ofline = 0;
	width = get_width_current_line(term) - term->x;
	if ((nb_ofline = charset_count(term, NEW_LINE[0], 0)) == 0)
		nb_ofline = term->width / term->ws_col;
	if (term->y < nb_ofline)
	{
		xtputs(term->tcaps[KEY_DOWN], 1, my_outc);
		term->x_index = term->x_index + width + 1;
		term->x = 0;
		term->y++;
	}
}

static void	move_in_column(uint64_t value, t_read *term)
{
	if (value == ALT_AW_UP && term->y > 0)
		move_col_up(term);
	else if (value == ALT_AW_DO)
		move_col_down(term);
}

/*
**	(CTRL+F) to jump one word forward
**	(CTRL+B) to jump one word backward
*/

void		jump_words(char *buff, t_read *term, u_int64_t value)
{
	if (value == CTRL_F)
	{
		if (term->buffer[term->x_index - term->prompt_len] != ' ')
			move_left(buff, term);
		while (term->x_index > term->prompt_len
			&& term->buffer[term->x_index - term->prompt_len] == ' ')
			move_left(buff, term);
		while (term->x_index > term->prompt_len
			&& term->buffer[term->x_index - term->prompt_len - 1] != ' ')
			move_left(buff, term);
	}
	else if (value == CTRL_B)
	{
		if (term->buffer[term->x_index - term->prompt_len] != ' ')
			move_right(buff, term);
		while (term->x_index < term->width
			&& term->buffer[term->x_index - term->prompt_len] == ' ')
			move_right(buff, term);
		while (term->x_index < term->width
			&& term->buffer[term->x_index - term->prompt_len] != ' ')
			move_right(buff, term);
	}
	else if (value == ALT_AW_UP || value == ALT_AW_DO)
		move_in_column(value, term);
}
