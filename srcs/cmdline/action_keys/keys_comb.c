/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:52:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

/*
**			CTRL_L => clear the screen but keep last buffer inserted
*/

void			clr_screen(t_read *term)
{
	char	*tmp;
	ssize_t	x_saved;
	ssize_t	i;

	i = 0;
	x_saved = term->x_index;
	tmp = ft_strdup(term->buffer);
	xtputs(term->tcaps[CLEAR], 1, my_outc);
	ft_dprintf(STDERR_FILENO, "%s%s%s%s", C_BOLD, C_Y, term->prompt, C_X);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(tmp, term);
	ft_strdel(&tmp);
	i = term->x_index - x_saved;
	while (i--)
		move_left(term);
}

static void		jump_backward(t_read *term)
{
	while (term->x_index > term->prompt_len &&
			term->buffer[term->x_index - term->prompt_len] == ' ')
		move_left(term);
	while (term->x_index > term->prompt_len &&
			term->buffer[term->x_index - term->prompt_len] != ' ')
	{
		move_left(term);
		if (term->buffer[term->x_index - term->prompt_len] == '\n')
			break ;
	}
}

static void		jump_forward(t_read *term)
{
	while (term->x_index < term->width
		&& term->buffer[term->x_index - term->prompt_len] == ' ')
		move_right(term);
	while (term->x_index < term->width
		&& term->buffer[term->x_index - term->prompt_len] != ' ')
	{
		move_right(term);
		if (term->buffer[term->x_index - term->prompt_len] == '\n')
			break ;
	}
}

/*
**			CTRL+F => to jump one word forward
**			CTRL+B => to jump one word backward
*/

void			jump_words(t_read *term, u_int64_t value)
{
	if (value == CTRL_B)
		jump_backward(term);
	else if (value == CTRL_F)
		jump_forward(term);
	else if (value == MOVE_UP || value == MOVE_DOWN)
		move_in_column(value, term);
}
