/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:36:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/12 17:21:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>
#include <unistd.h>

void	wait_for_job(t_core *shell, t_lst *jobs, t_job *job)
{
	pid_t	pid;
	int		status;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (mark_process_status(shell, jobs, pid, status)
			&& !job_is_stopped(job) && !job_is_completed(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	if (job_is_stopped(job) && !job_is_completed(job))
		do_job_notification(shell, shell->job_list, FALSE);
}

void	wait_for_process(t_core *shell, t_lst *jobs, t_process *process)
{
	pid_t	pid;
	int		status;

	pid = waitpid(process->pid, &status, WUNTRACED);
	mark_process_status(shell, jobs, pid, status);
	do_job_notification(shell, shell->launched_jobs, TRUE);
	if (WIFSTOPPED(status)
	&& (WSTOPSIG(status) == SIGTSTP || WSTOPSIG(status) == SIGSTOP))
		do_job_notification(shell, shell->job_list, FALSE);
}
