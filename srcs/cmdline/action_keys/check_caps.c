/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/12 11:17:19 by fcatusse         ###   ########.fr       */
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

static u_int8_t	return_key(t_read *term)
{
	if (term->x_index < term->width)
	{
		goto_prompt(term);
		ft_dprintf(STDOUT_FILENO, "%s", term->buffer);
	}
	ft_dprintf(STDERR_FILENO, "\n");
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

u_int8_t		check_caps(const char *buff, t_core *shell)
{
	u_int64_t	value;

	value = get_mask(buff);
	ak_clipboard(&shell->term, buff, &value);
	if (value == CTRL_D)
		return (ctrl_delete(&shell->term));
	if (ft_is_print(*buff))
		insert_in_buffer(buff, &shell->term);
	if (value == TAB_KEY)
		tab_key(shell);
	if (value == CTRL_R)
		research_mode(&shell->term);
	if (cursor_motion(&shell->term, value))
		return (TRUE);
	if (value == RETURN_KEY)
		return (return_key(&shell->term));
	check_keys_comb(&shell->term, value);
	return (TRUE);
}
