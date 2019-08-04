/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/02 15:03:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Combination of Keys
** Ctrl + l to clear the screen
** Ctrl + a && HOME key to move the cursor to the beginning of line
** Ctrl + e && END key to move move the cursor to the end of line
** Ctrl + k to clear from the cursor to the end of line
** Alt + b to jump one word backward
** Alt + f to jump one word forward
*/

void	check_keys_comb(char *buf, t_read *line)
{
	if (*buf == 12)
	{
		tputs(tgetstr("cl", NULL), 1, my_outc);
		display_prompt(line);
	}
	else if (*buf == 1 || (buf[0] == 27 && buf[1] == 91 && buf[2] == 72))
		while (line->x > line->prompt_len)
			move_left(buf, line);
	else if (*buf == 5 || (buf[0] == 27 && buf[1] == 91 && buf[2] == 70))
		while (line->x < line->width)
			move_right(buf, line);
	else if (*buf == 11)
		while (line->x < line->width)
			del_key(line);
	else
		jump_words(buf, line);
}

/*
** Interpret and insert char in buffer
** Tab key to turn on auto complete mode
** Right/Left arrows keys to move cursor in line
** Up/Down arrows keys to navigate through history
** Enter key to return the line
** Backspace/Delete keys to delete character in line
*/

uint8_t		check_caps(char *buf, t_read *line)
{
	if (buf[0] == '\t')
		auto_complete_mode(buf, line);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		move_key_up(line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		move_key_down(line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		move_right(buf, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		move_left(buf, line);
	else if (buf[0] == 10)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
		del_key(line);
	else if (buf[0] == 127)
		bs_key(buf, line);
	else if (is_print(buf[0]))
		insert_in_buffer(buf, line);
	else
		check_keys_comb(buf, line);
	return (TRUE);
}