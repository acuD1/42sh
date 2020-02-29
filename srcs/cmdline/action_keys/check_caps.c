/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/29 15:37:18 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Combination of Keys :
**	CTRL + L to clear the screen
**	CTRL + A && HOME key to move the cursor to the beginning of input
**	CTRL + E && END key to move move the cursor to the end of input
**	CTRL + K to clear from the cursor to the end of input
**	CTRL + B to jump one word backward
**	CTRL + F to jump one word forward
*/

static void		check_keys_comb(const char *buff, t_read *term, u_int64_t value)
{
	int		i;

	i = term->width - term->x_index;
	if (value == CTRL_L)
		clr_screen(term);
	else if (value == CTRL_A || value == HOME)
		while (term->x_index > term->prompt_len)
			move_left(buff, term);
	else if (value == CTRL_E || value == END_LE)
		while (term->x_index < term->width)
			move_right(buff, term);
	else if (value == CTRL_K)
		while (i--)
			del_key(term);
	else
		jump_words(buff, term, value);
}

static u_int8_t	cursor_motion(const char *buff, t_read *term, u_int64_t value)
{
	if (value == ARROW_UP)
		move_key_up(term);
	else if (value == ARROW_DOWN)
		move_key_down(term);
	else if (value == ARROW_RIGHT)
		move_right(buff, term);
	else if (value == ARROW_LEFT)
		move_left(buff, term);
	else if (value == DEL_KEY)
		del_key(term);
	else if (value == BS_KEY)
		bs_key(buff, term);
	else
		return (FALSE);
	return (TRUE);
}

static void		tab_key(t_read *term, u_int64_t *value)
{
	auto_complete_mode(term);
	*value = get_mask(term->ac_tmp);
	if (term->tmp_buff && ft_is_print(*term->ac_tmp))
		insert_in_buffer(term->ac_tmp, term);
	ft_strdel(&term->ac_tmp);
}

/*
**		CTRL+D del char on cursor if buffer isnt empty
*/

static int8_t	ctrl_delete(t_read *term)
{
	if (term->status == CMD_SUBPROMPT)
	{
		if (!*term->buffer)
		{
			term->flag = TRUE;
			return (FALSE);
		}
	}
	del_key(term);
	return (TRUE);
}

/*
**		Interpret and insert char in bufffer
**		CTRL+R to launch history research
**		Tab key to turn on auto complete mode
**		Right/Left arrows keys to move cursor in input
**		Up/Down arrows keys to navigate through history
**		Enter key to return the input
**		Backspace/Delete keys to delete character in input
*/

u_int8_t		check_caps(const char *buff, t_read *term)
{
	u_int64_t	value;

	value = get_mask(buff);
	feature(term, value);
	if (value == CTRL_D)
		return (ctrl_delete(term));
	if (value == TAB_KEY)
		tab_key(term, &value);
	else if (ft_is_print(*buff))
		insert_in_buffer(buff, term);
	if (value == CTRL_R)
		research_mode(term);
	if (cursor_motion(buff, term, value))
		return (TRUE);
	if (value == RETURN_KEY)
	{
		if (*term->prompt || (!*term->prompt && *term->buffer))
			ft_dprintf(STDERR_FILENO, "\n");
		return (FALSE);
	}
	check_keys_comb(buff, term, value);
	return (TRUE);
}
