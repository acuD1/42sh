/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/01 17:10:43 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	  Termcaps capabilities:
**	  - `up' => to move the cursor vertically up one input
**	  - `cr' => to move the cursor to the beginning of the input it is on
**	  - `clr_inputs' => to clear input from the cursor and following inputs
*/

void	goto_prompt(t_read *term)
{
	while (term->y-- > 0)
		xtputs(term->tcaps[KEY_UP], 1, my_outc);
	xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	if (term->sub_prompt > 0)
		display_subprompt(term, PS2);
	else
		display_prompt(term);
}

/*
**	  Display prompt as the current directory
**	  Store some datas for pressed keys
*/

void	display_prompt(t_read *term)
{
	ft_bzero(term->prompt, 10);
	ft_strcpy(term->prompt, PS1);
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term->sub_prompt = 0;
	term->flag = 0;
	term->cmd = NULL;
	ft_printf("%s%s%s%s", C_BOLD, C_Y, term->prompt, C_X);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
}

/*
**	  Clear the last buffer/input inserted & Display current prompt
**	  Launch input edition: read stdin until enter key is pressed
**	  The current buffer is saved in a history list
*/

int8_t	end_of_file(char *buff, t_read *term)
{
	t_core	*shell;

	shell = get_core(NULL);
	if (!*term->buffer && get_mask(buff) == CTRL_D)
	{
		if (term->status == CMD_SUBPROMPT)
		{
			term->flag = TRUE;
			return (FALSE);
		}
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		reset_config(shell);
		write_history(term);
		return (TRUE);
	}
	return (FALSE);
}

int8_t	init_prompt(t_core *shell)
{
	char	buff[READ_SIZE + 1];

	shell->term.status = CMD_PROMPT;
	ft_bzero(buff, READ_SIZE);
	shell->term.buffer = ft_memalloc(BUFF_SIZE);
	init_config(shell);
	init_termcaps(&shell->term);
	display_prompt(&shell->term);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (end_of_file(buff, &shell->term) == TRUE)
			return (FAILURE);
		if (check_caps(buff, &shell->term) == TRUE)
			ft_bzero(buff, READ_SIZE);
		else
			break ;
	}
	shell->term.status = CMD_DONE;
	if (check_subprompt(&shell->term) == FALSE)
		check_expansions(&shell->term);
	reset_config(shell);
	return (SUCCESS);
}
