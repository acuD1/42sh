/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/21 23:16:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	  Termcaps capabilities:
**	  - `up' => to move the cursor vertically up one input
**	  - `cr' => to move the cursor to the beginning of the input it is on
**	  - `clr_inputs' => to clear input from the cursor and following inputs
*/

void			goto_prompt(t_read *term)
{
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
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term->sub_prompt = 0;
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
		ft_putstr_fd("exit\n", STDERR_FILENO);
		if (are_jobs_done(shell, shell->launched_jobs) != TRUE)
		{
			write(STDERR_FILENO, "There are stopped jobs.\n", 24);
			return (FALSE);
		}
		reset_config(shell);
		write_history(&shell->term);
		return (TRUE);
	}
	return (FALSE);
}

void			get_prompt_value(t_core *shell, const char *key)
{
	t_db	*db;

	db = NULL;
	if ((db = search_db(shell->env, key)) == NULL)
	{
		shell->term.prompt = ft_strnew(0);
		return ;
	}
	if (!ft_strcmp(db->value, PS1))
		shell->term.prompt = ft_strsub(db->value, 1, 10);
	else if (!ft_strcmp(db->value, PS2))
		shell->term.prompt = ft_strsub(db->value, 1, 2);
	else
		shell->term.prompt = ft_strdup(db->value);
}

int8_t			init_prompt(t_core *shell)
{
	char	buff[READ_SIZE + 1];

	shell->term.status = CMD_PROMPT;
	ft_bzero(buff, READ_SIZE);
	shell->term.buffer = ft_memalloc(BUFF_SIZE);
	set_termconfig(shell);
	if (init_termcaps(&shell->term) == FAILURE)
		quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
	get_prompt_value(shell, "PS1");
	display_prompt(&shell->term);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (end_of_file(shell, buff) == TRUE)
			return (FAILURE);
		if (check_caps(buff, &shell->term) == TRUE)
			ft_bzero(buff, READ_SIZE);
		else if (*shell->term.prompt
			|| (!*shell->term.prompt && shell->term.buffer))
			break ;
	}
	shell->term.status = CMD_DONE;
	if (check_subprompt(shell) == FALSE)
		check_expansions(&shell->term);
	reset_config(shell);
	return (SUCCESS);
}
