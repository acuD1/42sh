/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/19 10:50:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	  Termcaps capabilities:
**	  - `up' => to move the cursor vertically up one input
**	  - `cr' => to move the cursor to the beginning of the input it is on
**	  - `clr_inputs' => to clear input from the cursor and following inputs
*/

void		goto_prompt(t_read *input)
{
	while (input->y-- > 0)
		xtputs(input->tcaps[KEY_UP], 1, my_outc);
	xtputs(input->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(input->tcaps[CLR_LINES], 1, my_outc);
	if (input->sub_prompt > 0)
		display_subprompt(input, PS2);
	else
		display_prompt(input);
}

/*
**	  Display prompt as the current directory
**	  Store some datas for pressed keys
*/

void		display_prompt(t_read *term)
{
	ft_bzero(term->prompt, 10);
	ft_strcpy(term->prompt, PS1);
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term->sub_prompt = 0;
	term->new_line = 0;
	ft_printf("%s%s%s%s", C_BOLD, C_Y, term->prompt, C_X);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
}

/*
**	  Clear the last buffer/input inserted & Display current prompt
**	  Launch input edition: read stdin until enter key is pressed
**	  The current buffer is saved in a history list
*/

void		init_prompt(t_core *shell, t_read *term)
{
	char	buff[READ_SIZE + 1];

	term->status = CMD_PROMPT;
	ft_bzero(buff, READ_SIZE);
	term->buffer = ft_memalloc(BUFF_SIZE);
	init_config(shell);
	init_termcaps(term);
	display_prompt(term);
//	while (term->status != CMD_DONE)
//	{
		while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
		{
			if (check_caps(buff, term) == TRUE)
				ft_bzero(buff, READ_SIZE);
			else
				break ;
		}
		term->status = CMD_DONE;
		if (check_subprompt(term) == FALSE)
		{
			// remove_newline(term);
			check_expansions(term);
		}
//	}
	reset_config(shell, term);
}
