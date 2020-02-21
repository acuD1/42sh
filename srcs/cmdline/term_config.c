/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:10:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/21 01:37:58 by mpivet-p         ###   ########.fr       */
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
	init_history(term);
}

/*
**	Store current config in a globale var
**	Set new attributes to term config
**	- ICANON enable non-canonical mode
**	- ECHO disable echo input characters
*/

int8_t	init_config(t_core *shell)
{
	if (tgetent(NULL, "xterm-256color") == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tgetent error\n");
		quit_shell(shell, EXIT_FAILURE, TRUE);
	}
	debug_ailleurs("/dev/ttys002", "GET");
	if (tcgetattr(STDIN_FILENO, &(shell->old_t)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tcgetattr error\n");
		quit_shell(shell, EXIT_FAILURE, TRUE);
	}
	shell->new_t = shell->old_t;
	shell->new_t.c_lflag &= ~(ICANON | ECHO);
	shell->new_t.c_cc[VMIN] = 1;
	shell->new_t.c_cc[VTIME] = 0;
	debug_ailleurs("/dev/ttys002", "SET");
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tcsetattr error\n");
		quit_shell(shell, EXIT_FAILURE, TRUE);
	}
	return (SUCCESS);
}

/*
**	Restore the old term config
**	Reset term when exit, before launch another shell, set term in bg..
*/

int8_t	reset_config(t_core *shell)
{
	debug_ailleurs("/dev/ttys002", "RESET");
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->old_t)) == FAILURE)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetattr failure\n");
		return (FAILURE);
	}
	ft_strdel(&shell->term.tmp_buff);
	ft_strdel(&shell->term.prompt);
	shell->term.cmd = NULL;
	return (SUCCESS);
}
