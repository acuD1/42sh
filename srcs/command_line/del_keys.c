/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:09 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/23 14:12:20 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Termcaps capabilities:
**	- `do' => to move the cursor vertically down one line
**	- `cr' => to move the cursor to the beginning of the line it is on
**	- `ce' => to clear from the cursor to the end of the current line
**	- `rc' => restore the cursor position
**	- `sc' => save cursor position
*/

void		clear_all_lines(t_read *input)
{
	int	j;

	j = (input->width / input->ws_col);
	tputs(tgetstr("dc", NULL), 1, my_outc);
	tputs(tgetstr("sc", NULL), 1, my_outc);
	while (j--)
	{
		tputs(tgetstr("do", NULL), 1, my_outc);
		tputs(tgetstr("cr", NULL), 1, my_outc);
		tputs(tgetstr("ce", NULL), 1, my_outc);
	}
	tputs(tgetstr("rc", NULL), 1, my_outc);
	tputs(tgetstr("sc", NULL), 1, my_outc);
	goto_prompt(input);
}

/*
**	Termcaps capabilities:
**	- `dc' => Delete one char position at the cursor
**	- `sc' => Save cursor position
**	- `rc' => Restore the cursor position
*/

void		del_key(t_read *input)
{
	int	i;
	int	x;
	int	y;
	int	w;

	if (input->x >= input->prompt_len * (input->y == 0 ? 1 : 0)
		&& input->x <= input->width)
	{
		i = input->x_index - input->prompt_len - 1;
		while (input->buffer[++i])
			input->buffer[i] = input->buffer[i + 1];
		x = input->x;
		i = input->x_index;
		y = input->y;
		w = input->width--;
		clear_all_lines(input);
		ft_putstr(input->buffer);
		input->x = x;
		input->x_index = i;
		input->y = y;
		input->width = w;
		tputs(tgetstr("rc", NULL), 1, my_outc);
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
