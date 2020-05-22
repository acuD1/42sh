/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:45:19 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/17 22:05:21 by fcatusse         ###   ########.fr       */
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

static void		jump_words(t_read *term, u_int64_t value)
{
	if (value == CTRL_B)
		jump_backward(term);
	else if (value == CTRL_F)
		jump_forward(term);
	else if (value == MOVE_UP || value == MOVE_DOWN)
		move_in_column(value, term);
}

/*
**	Combination of Keys :
**	CTRL + L to clear the screen
**	CTRL + A && HOME key to move the cursor to the beginning of input
**	CTRL + E && END key to move move the cursor to the end of input
**	CTRL + N to clear from the cursor to the end of input
**	CTRL + B to jump one word backward
**	CTRL + F to jump one word forward
*/

void			check_keys_comb(t_read *term, u_int64_t value)
{
	ssize_t	i;

	i = term->width - term->x_index;
	if (value == CTRL_L)
		clr_screen(term);
	else if (value == CTRL_A || value == HOME)
		while (term->x_index > term->prompt_len)
			move_left(term);
	else if (value == CTRL_E || value == END_LE)
		while (term->x_index < term->width)
			move_right(term);
	else if (value == CTRL_N)
		while (i--)
			del_key(term);
	else
		jump_words(term, value);
}
