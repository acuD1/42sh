/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/08 21:20:20 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			mark_process_status(t_core *shell, pid_t pid, int status)
{
	t_process	*process;

	if (pid > 0)
	{
		process = find_process(shell->launched_jobs, pid);
		if (process && process->pid == pid)
		{
			process->status = status;
			if (WIFSTOPPED(status))
				process->stopped = TRUE;
			else
			{
				process->completed = TRUE;
				status_handler(shell, status);
			}
			return (SUCCESS);
		}
		dprintf(STDERR_FILENO, "42sh: (%d) no child process\n", pid);
	}
	else if (pid != 0)
		dprintf(STDERR_FILENO, "42sh: waitpid error (mark_process_status)\n");
	return (FAILURE);
}

static void		update_status(t_core *shell)
{
	pid_t	pid;
	int		status;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (pid > 0 && !mark_process_status(shell, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

static void		format_job_info(t_job *job, const char *status)
{
	dprintf(STDERR_FILENO, "[%i]   %s\t\t%s\n", job->id, status, job->command);
}

static void		free_job(t_core *shell, t_lst *job)
{
	t_lst	*ptr;

	ptr = shell->launched_jobs;
	if (shell->launched_jobs != job)
	{
		while (ptr && ptr->next != job)
			ptr = ptr->next;
		ptr->next = job->next;
	}
	else
		shell->launched_jobs = job->next;

	// freeing job link
	free_process_list(job->content);
	ft_strdel(&(((t_job*)job->content)->command));
	free(job);
}

int8_t		do_job_notification(t_core *shell)
{
	t_lst *job;
	t_lst *jnext;
	t_job *ptr;

	/* Update status information for child processes.	*/
	if (shell->launched_jobs)
		update_status(shell);
	job = shell->launched_jobs;
	while (job)
	{
		ptr = ((t_job*)job->content);
		jnext = job->next;

		if (job_is_completed(ptr))
		{
			format_job_info(ptr, "Done");
			free_job(shell, job);
			job = NULL;
			ptr = NULL;
		}
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			format_job_info(ptr, "Stopped");
			ptr->notified = 1;
		}
		job = jnext;
	}
	return (SUCCESS);
}
