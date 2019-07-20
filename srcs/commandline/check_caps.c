/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:13 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/20 18:33:39 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

/*
** Combination of Keys
** Ctrl + l to clear the screen
** Ctrl + a to move the cursor to the beginning of line
** Ctrl + e to move move the cursor to the end of line
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
	else if (*buf == 1)
		while (line->x > line->prompt_len)
			move_left(buf, line);
	else if (*buf == 5)
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
** Right/Left arrows keys to move cursor in line
** Up/Down arrows keys to navigate through history
** Enter key to return the line
** Backspace/Delete keys to delete character in line
*/

int	check_caps(char *buf, t_read *line)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		move_key_up(line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		move_key_down(line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		move_right(buf, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		move_left(buf, line);
	else if (buf[0] == '\n')
	{
		ft_putchar('\n');
		return (0);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
		del_key(line);
	else if (buf[0] == 127)
		bs_key(buf, line);
	else if (is_print(buf[0]))
		insert_in_buffer(buf, line);
	else
		check_keys_comb(buf, line);
	return (1);
}
