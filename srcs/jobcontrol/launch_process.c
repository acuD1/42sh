/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/13 23:38:27 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>
#include <errno.h>

void		reset_signals(void)
{
	int		i;

	i = 0;
	while (i++ < SIGUSR2)
		signal(i, SIG_DFL);
}

static void	put_process_in_grp(t_process *process)
{
	process->pid = getpid();
	if (process->pgid == -1)
		process->pgid = process->pid;
	if (process->stopped == FALSE
		&& setpgid(process->pid, process->pgid) != SUCCESS)
	{
		perror("test");
		dprintf(STDERR_FILENO, "42sh: setpgid error\n");
		exit(EXIT_FAILURE);
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

int8_t		launch_blt(t_core *shell, t_process *process, int *fds)
{
	int		blt;

	if (fds[0] == STDIN_FILENO && fds[1] == STDOUT_FILENO && process->av
		&& (blt = is_a_blt(process->av[0])) != FAILURE)
	{
		process->status = call_builtin(shell, process, blt);
		process->completed = TRUE;
		shell->status = process->status;
		return (SUCCESS);
	}
	return (FAILURE);
}

void		launch_process
	(t_core *shell, t_process *process, int infile, int outfile)
{
	int		fds[2];
	int		blt;
	int		ret;

	if (shell->mode & I_MODE)
	{
		reset_signals();
		put_process_in_grp(process);
	}
	redir_pipes(&infile, &outfile);
	fds[0] = infile;
	fds[1] = outfile;
	if (process->av)
	{
		if ((blt = is_a_blt(process->av[0])) != FAILURE)
			exit(call_builtin(shell, process, blt));
	}
	ret = execve(process->bin, process->av, process->envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	exit(1);
}
