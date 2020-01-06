/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/06 21:52:49 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			mark_process_status(t_core *shell, pid_t pid, int status)
{
	t_process	*process;

	if (pid > 0)
	{
		process = find_process(shell->job_list, pid);
		if (process && process->pid == pid)
		{
			process->status = status;
			if (WIFSTOPPED(status))
				process->stopped = TRUE;
			else
			{
				process->completed = TRUE;
				process->status = WEXITSTATUS(status);
				shell->status = process->status;
				if (WIFSIGNALED(status))
					dprintf(STDERR_FILENO, "\n%d: Terminated by signal %d\n", pid, WTERMSIG(process->status));
			}
			return (SUCCESS);
		}
		dprintf(STDERR_FILENO, "42sh: (%d) no child process\n", pid);
	}
	else if (pid != 0)
		dprintf(STDERR_FILENO, "42sh: waitpid error\n");
	return (FAILURE);
}

static void		update_status(t_core *shell)
{
	pid_t	pid;
	int		status;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(shell, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

static void		format_job_info(t_job *job, const char *status)
{
	dprintf(STDERR_FILENO, "%ld (%s):\t%s\n", (long)job->pgid, status, job->command);
}

static void		free_job(t_core *shell, t_lst *job)
{
	t_lst	*ptr;

	ptr = shell->job_list;
	if (shell->job_list != job)
	{
		while (ptr && ptr->next != job)
			ptr = ptr->next;
		ptr->next = job->next;
	}
	else
		shell->job_list = job->next;

	/* freeing job link */
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
	update_status(shell);
	job = shell->job_list;
	while (job)
	{
		ptr = ((t_job*)job->content);
		jnext = job->next;

		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.	*/
		if (job_is_completed(ptr))
		{
			format_job_info(ptr, "Done");
			free_job(shell, job);
			ptr = NULL;
		}

		/* Notify the user about stopped jobs,
		   marking them so that we won’t do this more than once.	*/
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			format_job_info(ptr, "Stopped");
			ptr->notified = 1;
		}
		job = jnext;
	}
	return (SUCCESS);
}
