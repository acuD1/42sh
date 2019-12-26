/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/26 10:21:14 by arsciand         ###   ########.fr       */
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

void		check_keys_comb(char *buff, t_read *term, uint64_t value)
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

/*
**		Check if is EOF (CTRL+D) to exit program is buffer is empty
*/

void		end_of_file(t_read *term, uint64_t value)
{
	t_core	*shell;

	shell = get_core(NULL);
	if (!ft_strcmp(term->buffer, "") && value == CTRL_D)
	{
		ft_putstr("exit\n");
		reset_config(shell);
		write_history(term);
		free_history(term);
		quit_shell(shell, 0, FALSE);
		//exit(0);
	}
}

uint8_t		cursor_motion(char *buff, t_read *term, uint64_t value)
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

/*
**		Interpret and insert char in bufffer
**		CTRL+R to launch history research
**		Tab key to turn on auto complete mode
**		Right/Left arrows keys to move cursor in input
**		Up/Down arrows keys to navigate through history
**		Enter key to return the input
**		Backspace/Delete keys to delete character in input
*/

uint8_t		check_caps(char *buff, t_read *term)
{
	uint64_t	value;

	value = get_mask(buff);
	if (is_print(*buff))
		insert_in_buffer(buff, term);
	if (value == CTRL_R)
		research_mode(term);
	if (value == TAB_KEY)
	{
		auto_complete_mode(buff, term);
		value = get_mask(buff);
	}
	if (cursor_motion(buff, term, value))
		return (TRUE);
	if (value == RETURN_KEY)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else
		check_keys_comb(buff, term, value);
	end_of_file(term, value);
	return (TRUE);
}
