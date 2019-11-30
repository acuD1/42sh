/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/12 09:41:10 by arsciand         ###   ########.fr       */
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

void		check_keys_comb(char *buff, t_read *input, uint64_t value)
{
	int	i;

	i = input->width - input->x_index;
	if (value == CTRL_L)
		clr_screen(input);
	else if (value == CTRL_A || value == HOME)
		while (input->x_index > input->prompt_len)
			move_left(buff, input);
	else if (value == CTRL_E || value == END_LE)
		while (input->x_index < input->width)
			move_right(buff, input);
	else if (value == CTRL_K)
		while (i--)
			del_key(input);
	else
		jump_words(buff, input, value);
}

/*
**		Check if is EOF (CTRL+D) to exit program is buffer is empty
*/

void		end_of_file(t_read *input, uint64_t value)
{
	if (!*input->buffer && value == CTRL_D)
	{
		ft_putstr("exit\n");
		reset_config(input);
		write_history(input);
		if (input->history)
		{
			while (input->history)
			{
				free(input->history->content);
				input->history = input->history->next;
			}
		}
		free(input->history);
		exit(0);
	}
}

uint8_t		cursor_motion(char *buff, t_read *input, uint64_t value)
{
	if (value == ARROW_UP)
		move_key_up(input);
	else if (value == ARROW_DOWN)
		move_key_down(input);
	else if (value == ARROW_RIGHT)
		move_right(buff, input);
	else if (value == ARROW_LEFT)
		move_left(buff, input);
	else if (value == DEL_KEY)
		del_key(input);
	else if (value == BS_KEY)
		bs_key(buff, input);
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

uint8_t		check_caps(char *buff, t_read *input)
{
	uint64_t	value;

	value = get_mask(buff);
	if (is_print(*buff))
		insert_in_buffer(buff, input);
	if (value == CTRL_R)
		research_mode(input);
	if (value == TAB_KEY)
	{
		auto_complete_mode(buff, input);
		value = get_mask(buff);
	}
	if (cursor_motion(buff, input, value))
	   return (TRUE);
	if (value == RETURN_KEY)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else
		check_keys_comb(buff, input, value);
	end_of_file(input, value);
	return (TRUE);
}
