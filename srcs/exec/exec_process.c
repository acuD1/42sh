/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/09 11:20:59 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <sys/wait.h>

/*
**	exec_process takes for parameter t_lst *env for now because we can set
**	a temporary environnement if we use the env builtin.
*/

static int8_t	job_part_completed(t_job *job, t_process *process)
{
	t_lst *ptr;

	ptr = job->process_list;
	while (ptr != NULL && ptr->content != process)
	{
		if (((t_process *)ptr->content)->completed != TRUE)
			return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}

static void		control_process
	(t_core *shell, t_job *job, t_process *process)
{
	if (process->pgid == -1)
		job->pgid = process->pid;
	process->pgid = job->pgid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: setpgid error (1)\n");
	if (process->stopped != TRUE && process->type != P_PIPE)
	{
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error (1)\n");
		if (process->pipe[0] != STDIN_FILENO)
			wait_for_job(shell, shell->job_list, job);
		else
			wait_for_process(shell, job, process);
		if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error (2)\n");
	}
	else
		process->stopped = FALSE;
}

static void		clear_fds(t_process *process)
{
	if (process->pipe[1] != STDOUT_FILENO)
		close(process->pipe[1]);
	if (process->pipe[0] != STDIN_FILENO)
		close(process->pipe[0]);
}

void			exec_process(t_core *shell, t_job *job, t_process *process)
{
	if (job_part_completed(job, process))
		job->pgid = -1;
	process->pgid = job->pgid;
	if (process->av)
		get_bin(shell, process);
	if ((process->pid = fork()) == 0)
		launch_process(shell, process);
	else if (process->pid < 0)
		print_and_quit(shell, "42sh: fork failure\n");
	clear_fds(process);
	if (shell->is_interactive == TRUE)
		control_process(shell, job, process);
	else if (process->type != P_PIPE)
		wait_for_process(shell, job, process);
}
