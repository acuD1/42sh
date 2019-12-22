/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:09 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/19 10:42:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Termcaps capabilities:
**	- `del' => Delete one char position at the cursor
**	- `clr_lines' => clear the line the cursor is on, and following lines
**	- `reset_cr' => restore the cursor position
**	- `save_cr' => save cursor position
*/

void		clear_all_lines(t_read *input)
{
	xtputs(input->tcaps[DEL_CR], 1, my_outc);
	xtputs(input->tcaps[SAVE_CR], 1, my_outc);
	xtputs(input->tcaps[CLR_LINES], 1, my_outc);
	xtputs(input->tcaps[RESTORE_CR], 1, my_outc);
	goto_prompt(input);
}

void		del_key(t_read *input)
{
	int		i;
	int		x;
	int		y;
	int		w;

	if (input->x >= input->prompt_len * (input->y == 0 ? 1 : 0)
		&& input->x <= input->width)
	{
		i = input->x_index - input->prompt_len - 1;
		while (input->buffer[++i])
			input->buffer[i] = input->buffer[i + 1];
		x = input->x;
		i = input->x_index;
		y = input->y;
		w = input->width - 1;
		clear_all_lines(input);
		ft_putstr(input->buffer);
		input->x = x;
		input->x_index = i;
		input->y = y;
		input->width = w;
		xtputs(input->tcaps[RESTORE_CR], 1, my_outc);
	}
}

/*
**	Backspace key function move the cursor one char on the left
**	Call del_key function to delete char from cursor position
*/

void		bs_key(char *buf, t_read *input)
{
	if ((input->y > 0 && input->x >= 0) || input->x > input->prompt_len)
	{
		move_left(buf, input);
		del_key(input);
	}
}
