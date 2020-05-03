/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:52:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static u_int8_t	cursor_motion(t_read *term, u_int64_t value)
{
	if (value == ARROW_UP)
		move_key_up(term);
	else if (value == ARROW_DOWN)
		move_key_down(term);
	else if (value == ARROW_RIGHT)
		move_right(term);
	else if (value == ARROW_LEFT)
		move_left(term);
	else if (value == DEL_KEY)
		del_key(term);
	else if (value == BS_KEY)
		bs_key(term);
	else
		return (FALSE);
	return (TRUE);
}

static void		tab_key(t_read *term, u_int64_t *value)
{
	auto_complete_mode(term);
	*value = get_mask(term->ac_tmp);
	if (term->ac_tmp && ft_is_print(*term->ac_tmp))
		insert_in_buffer(term->ac_tmp, term);
	ft_strdel(&term->ac_tmp);
}

/*
**		CTRL+D del char on cursor if buffer isnt empty
*/

static u_int8_t	ctrl_delete(t_read *term)
{
	if (term->status == CMD_SUBPROMPT)
	{
		if (!*term->buffer)
		{
			term->status = CMD_DONE;
			return (FALSE);
		}
	}
	del_key(term);
	return (TRUE);
}

static int8_t	return_key(t_read *term)
{
	if (*term->prompt || (!*term->prompt && *term->buffer))
	{
		if (term->x_index < term->width)
		{
			goto_prompt(term);
			ft_dprintf(STDERR_FILENO, "%s", term->buffer);
		}
		ft_dprintf(STDERR_FILENO, "\n");
	}
	return (FALSE);
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
	ak_clipboard(term, buff, &value);
	if (value == CTRL_D)
		return (ctrl_delete(term));
	if (value == TAB_KEY && (term->x_index == term->width))
		tab_key(term, &value);
	else if (ft_is_print(*buff))
		insert_in_buffer(buff, term);
	if (value == CTRL_R && term->sub_prompt == FALSE)
		research_mode(term);
	if (cursor_motion(term, value))
		return (TRUE);
	if (value == RETURN_KEY)
		return (return_key(term));
	check_keys_comb(term, value);
	return (TRUE);
}
