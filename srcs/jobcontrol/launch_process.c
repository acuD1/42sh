/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/04 20:00:27 by mpivet-p         ###   ########.fr       */
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
	(void)shell;
	process->pid = getpid();
	if (process->pgid == 0)
		process->pgid = process->pid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
		exit(EXIT_FAILURE);
	}
//	if (process->stopped != TRUE)
//	{
//	//	write(1, "f\n", 2);
//	//	printf("%i\n", process->pgid);
//	//	printf("%i\n", process->pid);
//	//	printf("%i\n", shell->terminal);
//	//	printf("%i\n", tcsetpgrp(shell->terminal, process->pgid));
//		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
//		{
//			write(1, "f\n", 2);
//			dprintf(STDERR_FILENO, "42sh: tcsetpgrp error\n");
//			exit(EXIT_FAILURE);
//		}
//		write(1, "z\n", 2);
//	}
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

int8_t		launch_blt(t_core *shell, t_process *process)
{
	int		blt;

	if (process->av && (blt = is_a_blt(process->av[0])) != FAILURE)
	{
		process->status = call_builtin(shell, process, blt);
		process->completed = TRUE;
		shell->status = process->status;
		return (SUCCESS);
	}
	return (FAILURE);
}

void	launch_process(t_core *shell, t_process *process, int infile, int outfile)
{
	if (shell->is_interactive)
	{
		reset_signals();
		put_process_in_grp(shell, process);
	}
	redir_pipes(&infile, &outfile);
	if (process->av)
	{
		if (launch_blt(shell, process) != FAILURE)
			exit(process->status);
		get_bin(shell, process);
	}
	call_bin(shell, process);
}
