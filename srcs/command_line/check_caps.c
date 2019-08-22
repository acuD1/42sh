/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/22 16:11:55 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Combination of Keys :
**	CTRL + L to clear the screen
**	CTRL + A && HOME key to move the cursor to the beginning of line
**	CTRL + E && END key to move move the cursor to the end of line
**	CTRL + K to clear from the cursor to the end of line
**	ALT + B to jump one word backward
**	ALT + F to jump one word forward
*/

void		check_keys_comb(char *buff, t_read *line)
{
	int	i;

	if (*buff == CLEAR_SCREEN)
	{
		i = line->x;
		tputs(tgetstr("cl", NULL), 1, my_outc);
		dprintf(STDOUT_FILENO, "%s%s<< %s >>%s ", C_BOLD, C_Y, line->prompt + 1, C_X);
		ft_putstr(line->buffer);
		tputs(tgetstr("ho", NULL), 1, my_outc);
		while (i--)
			tputs(tgetstr("nd", NULL), 1, my_outc);
	}
	else if (*buff == BEGINNING_LINE || (buff[0] == 27 && buff[1] == 91 && buff[2] == 72))
		while (line->x_index > line->prompt_len)
			move_left(buff, line);
	else if (*buff == END_LINE || (buff[0] == 27 && buff[1] == 91 && buff[2] == 70))
		while (line->x_index < line->width)
			move_right(buff, line);
	else if (*buff == CLEAR_LINE)
		while (line->x_index < line->width)
			del_key(line);
	else
		jump_words(buff, line);
}

/*
**	Check if is EOF (CTRL+D) to exit program
*/

void		end_of_file(char *buff, t_read *line)
{
	if (*buff == END_OF_FILE)
	{
		ft_putstr("exit\n");
		reset_config(line);
		exit(0);
	}
}

/*
**	Interpret and insert char in bufffer
**	Tab key to turn on auto complete mode
**	Right/Left arrows keys to move cursor in line
**	Up/Down arrows keys to navigate through history
**	Enter key to return the line
**	Backspace/Delete keys to delete character in line
*/

uint8_t		check_caps(char *buff, t_read *line)
{
	if (*buff == TAB_KEY)
		auto_complete_mode(buff, line);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
		move_key_up(line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
		move_key_down(line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		move_right(buff, line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		move_left(buff, line);
	else if (*buff == RETURN_KEY)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126)
		del_key(line);
	else if (*buff == BS_KEY)
		bs_key(buff, line);
	else if (is_print(*buff))
		insert_in_buffer(buff, line);
	else
		check_keys_comb(buff, line);
	end_of_file(buff, line);
	return (TRUE);
}
