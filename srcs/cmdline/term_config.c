/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:10:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/09 17:16:40 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <term.h>
#include <unistd.h>
#include <stdlib.h>

void	init_cmd_line(t_core *shell, t_read *term)
{
	term->history = NULL;
	term->history_index = NULL;
	term->sub_prompt = FALSE;
	term->search = 0;
	term->ctrl_c = 0;
	term->buffer = NULL;
	term->tmp_buff = NULL;
	term->prompt = NULL;
	term->cpy = NULL;
	if (get_size(term) != SUCCESS)
		quit_shell(shell, EXIT_FAILURE, TRUE);
	shell->term.history = term->history;
	init_history(shell);
}

/*
**	Store current config in a globale var
**	Set new attributes to term config
**	- ICANON enable non-canonical mode
**	- ECHO disable echo input characters
*/

int8_t	init_config(t_core *shell)
{
	if (tcgetattr(STDIN_FILENO, &(shell->old_t)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tcgetattr error\n");
		quit_shell(shell, EXIT_FAILURE, FALSE);
	}
	if (init_termcaps(&(shell->term)) == FAILURE)
		quit_shell(shell, EXIT_FAILURE, FALSE);
	shell->new_t = shell->old_t;
	shell->new_t.c_lflag &= (size_t)~(ICANON | ECHO);
	shell->new_t.c_cc[VMIN] = 1;
	shell->new_t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		quit_shell(shell, EXIT_FAILURE, FALSE);
	}
	return (SUCCESS);
}

void	set_termconfig(t_core *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		quit_shell(shell, 1, FALSE);
	}
}

/*
**	Restore the old term config
**	Reset term when exit, before launch another shell, set term in bg..
*/

int8_t	reset_config(t_core *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->old_t)) == FAILURE)
	{
		return (FAILURE);
	}
	ft_strdel(&shell->term.tmp_buff);
	ft_strdel(&shell->term.prompt);
	return (SUCCESS);
}
