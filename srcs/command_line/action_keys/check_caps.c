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

	if (value == CTRL_L)
		clr_screen(input);
	else if (value == CTRL_A || value == HOME)
		while (input->x_index > input->prompt_len)
			move_left(buff, input);
	else if (value == CTRL_E || value == END_LE)
		while (input->x_index < input->width)
			move_right(buff, input);
	else if (value == CTRL_K)
	{
		i = input->x_index;
		while (i++ < input->width)
			del_key(input);
	}
	else
		jump_words(buff, input, value);
}

/*
**		Check if is EOF (CTRL+D) to exit program is buffer is empty
*/

void		end_of_file(t_read *input, uint64_t value)
{
	// if (!ft_strcmp(input->buffer, "") && value == CTRL_D)
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

uint8_t		charset_count(char *str, char charset, int index)
{
	int	i;
	int	count;

	i = index - 1;
	// i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == charset)
			count++;
		// if (str[i] == ';')
			// return (count);
	}
	return (count);

}


uint8_t backslash_prompt(t_read *input, int index)
{

	printf("INDEX %d\n", index);
	ft_putchar('\n');
	// printf("%d\n", charset_count(input->buffer, '\\', 0));
	if (charset_count(input->buffer, '\\', index - 1) % 2 != 0)
	{
		input->buffer[ft_strlen(input->buffer)] = ';';
		display_subprompt(input, PS2);
		input->cptflag = 1;
		return (TRUE);
	}
	else
	{
		input->cptflag = 0;
		return (FALSE);
	}
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
	if (value == RETURN_KEY)
	{
		printf("[%s cpt %d]\n", input->buffer, input->x_index - input->prompt_len);
		if (input->buffer[input->x_index - input->prompt_len - 1] == '\\')
			return (backslash_prompt(input, input->x_index - input->prompt_len));
		insert_newline_in_buff(input);
		ft_putchar('\n');
		//ESCAPE SEQUENCE NEED TO CREATE FCT TO MANAGE ALL SUBPROMPT
		return (FALSE);
	}
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
	else
		check_keys_comb(buff, input, value);
	end_of_file(input, value);
	return (TRUE);
}
