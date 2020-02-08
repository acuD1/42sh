/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/08 04:50:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	(t_core *shell, t_job *job, t_process *process, int *fds)
{
	if (process->pgid == -1)
		job->pgid = process->pid;
	process->pgid = job->pgid;
	if (process->stopped != TRUE && fds[1] == STDOUT_FILENO)
	{
		if (setpgid(process->pid, process->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: setpgid error\n");
		if (tcsetpgrp(shell->terminal, process->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
		wait_for_process(shell, shell->job_list, process);
		if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
	}
	else if (fds[1] == STDOUT_FILENO)
		wait_for_process(shell, shell->job_list, process);
	else
		process->stopped = FALSE;
}

void			exec_process
	(t_core *shell, t_job *job, t_process *process, int *fds)
{
	if (job_part_completed(job, process))
		job->pgid = -1;
	process->pgid = job->pgid;
	if (process->av)
		get_bin(shell, process);
	if ((process->pid = fork()) == 0)
		launch_process(shell, process, fds[0], fds[1]);
	else if (process->pid < 0)
		print_and_quit(shell, "42sh: fork failure\n");
	if (shell->mode & I_MODE)
		control_process(shell, job, process, fds);
}
