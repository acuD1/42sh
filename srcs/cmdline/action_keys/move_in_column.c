/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_in_column.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 22:40:28 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 16:33:12 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	SHIFT + ARROW_UP to move up one input in the same column
**	Termcaps capabilities :	`up' to go up one input in same col
**				`nd' to move the cursor on right
*/

static void	move_col_up(t_read *term)
{
	ssize_t	width;
	ssize_t	new_y;

	new_y = term->y - 1;
	width = term->ws_col - term->x - 1;
	while (term->y > new_y)
		move_left(term);
	if (get_width_current_line(term) == term->ws_col - 1)
		while (width--)
			move_left(term);
}

/*
**	SHIFT + ARROW_DOWN to move down one line at the first column
**	Termcaps capabilities : `down' to move cursor down at beginning of input
*/

static void	move_col_down(t_read *term)
{
	ssize_t	width;
	ssize_t	nb_ofline;

	nb_ofline = 0;
	width = get_width_current_line(term) - term->x;
	if ((nb_ofline = charset_count(term, NEW_LINE[0], 0)) == 0)
		nb_ofline = term->width / term->ws_col;
	if (term->y < nb_ofline)
	{
		width = term->ws_col;
		while (width--)
		{
			move_right(term);
			if (term->x == 0 && (get_width_current_line(term) < width))
				width = get_width_current_line(term);
		}
	}
}

void		move_in_column(u_int64_t value, t_read *term)
{
	if (value == MOVE_UP && term->y > 0)
		move_col_up(term);
	else if (value == MOVE_DOWN)
		move_col_down(term);
}
