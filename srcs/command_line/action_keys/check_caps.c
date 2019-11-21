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

uint8_t		charset_count(t_read *input, char charset, int *i)
{
	int	count;

	count = 0;
	printf("[%s]\n", input->buffer);
	while (input->buffer[*i])
	{
		if (input->buffer[*i] == charset)
			count++;
		(*i)++;
	}
	if (input->buffer[*i - 1] != charset)
		return (FALSE);
	return (count);

}


uint8_t		check_backslash(t_read *input)
{
	int	buff_i;
	char	*buff_r;

	// buff_i = input->x_index - input->prompt_len - 1;
	buff_r = ft_strrchr(input->buffer, ';');
	if (!buff_r)
		buff_i = 0;
	else
		buff_i = ft_strlen(input->buffer) - ft_strlen(buff_r);
	if (input->buffer[ft_strlen(input->buffer) - 1] == '\\')
	{
		printf("BUFBFUF {%s   %d}\n", buff_r, buff_i);
		if (charset_count(input, '\\', &buff_i) % 2 != 0)
		{
			insert_char_in_buffer(';', input, input->x_index - input->prompt_len);
			xtputs(input->tcaps[KEY_LEFT], 1, my_outc);
			xtputs(input->tcaps[DEL_CR], 1, my_outc);
			display_subprompt(input, PS2);
			return (TRUE);
		}
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
		// ft_putchar('\n');
		if (check_backslash(input) == TRUE)
			return (TRUE);
		else
		{
			insert_newline_in_buff(input);
			return (FALSE);
		}
	}
	else
		check_keys_comb(buff, input, value);
	end_of_file(input, value);
	return (TRUE);
}
