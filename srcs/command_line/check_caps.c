/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/17 13:24:13 by fcatusse         ###   ########.fr       */
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

void		check_keys_comb(char *buff, t_read *line)
{
	int	i;

	if (*buff == CLEAR_SCREEN)
		clr_screen(line);
	else if (*buff == BEGINNING_LINE || (buff[0] == 27 && buff[1] == 91 && buff[2] == 72))
		while (line->x_index > line->prompt_len)
			move_left(buff, line);
	else if (*buff == END_LINE || (buff[0] == 27 && buff[1] == 91 && buff[2] == 70))
		while (line->x_index < line->width)
			move_right(buff, line);
	else if (*buff == CLEAR_LINE)
	{
		i = line->x_index;
		while (i++ < line->width)
			del_key(line);
	}
	else
		jump_words(buff, line);
}

/*
**		Check if is EOF (CTRL+D) to exit program is buffer is empty
*/

void		end_of_file(char *buff, t_read *line)
{
	if (!ft_strcmp(line->buffer, "") && *buff == END_OF_FILE)
	{
		ft_putstr("exit\n");
		reset_config(line);
		write_history(line);
		//free history
		exit(0);
	}
}

uint8_t		cursor_motion(char *buff, t_read *line)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
		move_key_up(line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
		move_key_down(line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		move_right(buff, line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		move_left(buff, line);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126)
		del_key(line);
	else if (*buff == BS_KEY)
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
	if (is_print(*buff))
		insert_in_buffer(buff, line);
	else if (*buff == CTRL_R)
		research_mode(&line);
	else if (*buff == TAB_KEY)
		auto_complete_mode(buff, line);
	else if (cursor_motion(buff, line))
		return (TRUE);
	else if (*buff == RETURN_KEY)
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else
		check_keys_comb(buff, line);
	end_of_file(buff, line);
	return (TRUE);
}
