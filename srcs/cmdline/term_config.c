/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:10:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/26 18:41:00 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "sh42.h"

void	init_cmd_line(t_core *shell, t_read *term)
{
	term->history = NULL;
	term->history_index = NULL;
	term->shell = shell;
	term->flag = 0;
	term->sub_prompt = 0;
	term->buffer = NULL;
	term->tmp_buff = NULL;
	term->cmd = NULL;
	term->prompt = NULL;
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
	if (init_termcaps(&(shell->term)) == FAILURE)
		quit_shell(shell, EXIT_FAILURE, FALSE);
	if (tcgetattr(STDIN_FILENO, &(shell->old_t)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tcgetattr error\n");
		quit_shell(shell, EXIT_FAILURE, FALSE);
	}
	shell->new_t = shell->old_t;
	shell->new_t.c_lflag &= ~(ICANON | ECHO);
	shell->new_t.c_cc[VMIN] = 1;
	shell->new_t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tcsetattr error\n");
		quit_shell(shell, EXIT_FAILURE, FALSE);
	}
	return (SUCCESS);
}

void	set_termconfig(t_core *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetattr failure\n");
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
		ft_dprintf(STDERR_FILENO, "42sh: tcsetattr failure\n");
		return (FAILURE);
	}
	ft_strdel(&shell->term.tmp_buff);
	ft_strdel(&shell->term.prompt);
	shell->term.cmd = NULL;
	return (SUCCESS);
}
