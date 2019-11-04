/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/04 21:53:54 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Combination of Keys :
**	CTRL + L to clear the screen
**	CTRL + A && HOME key to move the cursor to the beginning of line
**	CTRL + E && END key to move move the cursor to the end of line
**	CTRL + K to clear from the cursor to the end of line
**	CTRL + B to jump one word backward
**	CTRL + F to jump one word forward
*/

void		check_keys_comb(char *buff, t_read *line, uint64_t value)
{
	int	i;

	if (value == CTRL_L)
		clr_screen(line);
	else if (value == CTRL_A || value == HOME)
		while (line->x_index > line->prompt_len)
			move_left(buff, line);
	else if (value == CTRL_E || value == END)
		while (line->x_index < line->width)
			move_right(buff, line);
	else if (value == CTRL_K)
	{
		i = line->x_index;
		while (i++ < line->width)
			del_key(line);
	}
	else
		jump_words(buff, line, value);
}

/*
**		Check if is EOF (CTRL+D) to exit program is buffer is empty
*/

void		end_of_file(t_read *line, uint64_t value)
{
	if (!ft_strcmp(line->buffer, "") && value == CTRL_D)
	{
		ft_putstr("exit\n");
		reset_config(line);
		write_history(line);
		if (line->history)
		{
			while (line->history)
			{
				free(line->history->content);
				line->history = line->history->next;
			}
		}
		free(line->history);
		exit(0);
	}
}

uint8_t		cursor_motion(char *buff, t_read *line, uint64_t value)
{
	if (value == ARROW_UP)
		move_key_up(line);
	else if (value == ARROW_DOWN)
		move_key_down(line);
	else if (value == ARROW_RIGHT)
		move_right(buff, line);
	else if (value == ARROW_LEFT)
		move_left(buff, line);
	else if (value == DEL_KEY)
		del_key(line);
	else if (value == BS_KEY)
		bs_key(buff, line);
	else
		return (FALSE);
	return (TRUE);
}

/*
**		Interpret and insert char in bufffer
**		CTRL+R to launch history research
**		Tab key to turn on auto complete mode
**		Right/Left arrows keys to move cursor in line
**		Up/Down arrows keys to navigate through history
**		Enter key to return the line
**		Backspace/Delete keys to delete character in line
*/

uint8_t		check_caps(char *buff, t_read *line)
{
	uint64_t	value;

	value = get_mask(buff);
	if (is_print(*buff))
		insert_in_buffer(buff, line);
	if (value == CTRL_R)
		research_mode(line);
	if (value == TAB_KEY)
	{
		auto_complete_mode(buff, line);
		value = get_mask(buff);
	}
	if (cursor_motion(buff, line, value))
	   return (TRUE);
	if (value == RETURN_KEY)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else
		check_keys_comb(buff, line, value);
	end_of_file(line, value);
	return (TRUE);
}
