/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/28 08:41:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include <unistd.h>

/*
**	  - `cr' => to move the cursor to the beginning of the input it is on
**	  - `clr_lines' => to clear line from the cursor and following inputs
*/

void			goto_prompt(t_read *term)
{
	if ((ssize_t)ft_strlen(term->prompt) > term->ws_col)
		term->y += (ssize_t)ft_strlen(term->prompt) / term->ws_col;
	while (term->y-- > 0)
		xtputs(term->tcaps[KEY_UP], 1, my_outc);
	xtputs(term->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	if (term->sub_prompt > 0)
		display_subprompt(term);
	else
		display_prompt(term);
}

/*
**	  Display prompt as the current directory
**	  Store some datas for pressed keys
*/

void			display_prompt(t_read *term)
{
	term->prompt_len = (ssize_t)ft_strlen(term->prompt);
	term->prompt_len = term->prompt_len % term->ws_col;
	term->x = term->prompt_len;
	term->y = 0;
	term->x_index = term->x;
	term->width = term->x;
	term->sub_prompt = FALSE;
	ft_dprintf(STDERR_FILENO, "%s%s%s%s", C_BOLD, C_Y, term->prompt, C_X);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
}

/*
**	  Clear the last buffer/input inserted & Display current prompt
**	  Launch input edition: read stdin until enter key is pressed
**	  The current buffer is saved in a history list
*/

static int8_t	end_of_file(t_core *shell, const char *buff)
{
	if (!*(shell->term).buffer && get_mask(buff) == CTRL_D)
	{
		shell->ac_flag = FAILURE;
		auto_complete_mode(NULL, shell, NULL);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		if (are_jobs_done(shell, shell->launched_jobs) != TRUE)
		{
			write(STDERR_FILENO, "There are stopped jobs.\n", 24);
			display_prompt(&(shell->term));
			return (FALSE);
		}
		reset_config(shell);
		write_history(shell);
		ft_strdel(&shell->term.cpy);
		return (TRUE);
	}
	return (FALSE);
}

int8_t			init_prompt(t_core *shell)
{
	char	buff[READ_SIZE + 1];

	shell->term.status = CMD_PROMPT;
	ft_bzero(buff, READ_SIZE + 1);
	shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
	set_termconfig(shell);
	get_prompt_value(shell, "PS1");
	display_prompt(&shell->term);
	while (read(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		shell->term.search = 0;
		shell->term.ctrl_c = 0;
		if (end_of_file(shell, buff) == TRUE)
			return (FAILURE);
		if (check_caps(buff, shell) == TRUE)
			ft_bzero(buff, READ_SIZE + 1);
		else if (*shell->term.prompt
			|| (!*shell->term.prompt && shell->term.buffer))
			break ;
	}
	shell->ac_flag = FAILURE;
	auto_complete_mode(NULL, shell, NULL);
	shell->term.status = CMD_DONE;
	return (SUCCESS);
}
