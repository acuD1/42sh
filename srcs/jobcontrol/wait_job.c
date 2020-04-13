/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:36:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/12 19:32:16 by mpivet-p         ###   ########.fr       */
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
}

static int8_t	process_is_last(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (((t_process*)ptr->content)->type == P_PIPE)
		ptr = ptr->next;	
	return (ptr->next == NULL);
}

void	wait_for_process(t_core *shell, t_job *job, t_process *process)
{
	pid_t	pid;
	int		status;

	pid = waitpid(process->pid, &status, WUNTRACED);
	mark_process_status(shell, shell->job_list, pid, status);
	if (WIFSIGNALED(status) || WIFSTOPPED(status))
		write(2, "\n", 1);
	if (shell->is_interactive && WIFSTOPPED(status)
	&& !process_is_last(job)
	&& (WSTOPSIG(status) == SIGTSTP || WSTOPSIG(status) == SIGSTOP))
	{
		split_job(shell, job);
	}
	else if (shell->is_interactive && WIFSTOPPED(status))
		do_job_notification(shell, shell->job_list, FALSE);
}
