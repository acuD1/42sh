/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:36:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:29:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>
#include <unistd.h>

static void		wait_pipe(t_core *shell, t_lst *jobs, t_job *job, int *status)
{
	t_lst	*ptr;
	pid_t	pid;

	ptr = job->process_list;
	pid = waitpid(((t_process*)ptr->content)->pid, status, WUNTRACED);
	ptr = ptr->next;
	while (mark_process_status(shell, jobs, pid, *status) && ptr
			&& ((t_process*)ptr->content)->pipe[0] != STDIN_FILENO)
	{
		pid = waitpid(WAIT_ANY, status, WUNTRACED);
		ptr = ptr->next;
	}
}

static int8_t	process_is_last(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (((t_process*)ptr->content)->type == P_PIPE)
		ptr = ptr->next;
	return (ptr->next == NULL);
}

void			wait_for_job(t_core *shell, t_lst *jobs, t_job *job)
{
	pid_t	pid;
	int		status;

	if (((t_process*)job->process_list->content)->type == P_PIPE)
		wait_pipe(shell, jobs, job, &status);
	else
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		while (mark_process_status(shell, jobs, pid, status)
				&& !job_is_stopped(job) && !job_is_completed(job))
			pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
	if (shell->is_interactive && !process_is_last(job)
		&& ((t_process*)job->process_list->content)->stopped == TRUE)
	{
		split_job(shell, job);
	}
	else if (shell->is_interactive && WIFSTOPPED(status))
		do_job_notification(shell, shell->job_list, FALSE);
}

void			wait_for_process(t_core *shell, t_job *job, t_process *process)
{
	pid_t	pid;
	int		status;

	pid = waitpid(process->pid, &status, WUNTRACED);
	mark_process_status(shell, shell->job_list, pid, status);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| WIFSTOPPED(status))
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
