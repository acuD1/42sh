/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/29 19:27:01 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		reset_signals(void)
{
	int	i;

	i = 0;
	while (i++ < SIGUSR2)
		signal(i, SIG_DFL);
}

static void	put_process_in_grp(t_core *shell, t_process *process)
{
	process->pid = getpid();
	if (process->pgid == 0)
		process->pgid = process->pid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
		exit(EXIT_FAILURE);
	}
	if (process->stopped != TRUE)
	{
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
		{
			dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
			exit(EXIT_FAILURE);
		}
	}
}

static void	redir_pipes(int *infile, int *outfile)
{
	if (*infile != STDIN_FILENO)
	{
		dup2(*infile, STDIN_FILENO);
		close(*infile);
	}
	if (*outfile != STDOUT_FILENO)
	{
		dup2(*outfile, STDOUT_FILENO);
		close(*outfile);
	}
}

int8_t		launch_process(t_core *shell, t_process *process, int infile, int outfile)
{
	if (shell->is_interactive)
	{
		reset_signals();
		put_process_in_grp(shell, process);
	}
	redir_pipes(&infile, &outfile);
	//call_bin
	return (SUCCESS);
}
