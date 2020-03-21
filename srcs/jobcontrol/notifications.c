/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/11 22:22:59 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>
#include <unistd.h>

void		update_status(t_core *shell)
{
	pid_t	pid;
	int		status;

	update_background_pid(shell);
	if (!shell->launched_jobs)
		return ;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (mark_process_status(shell, shell->launched_jobs, pid, status))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
}

void		format_job_info(t_job *job)
{
	static char	*messages[4] = {"Stopped(SIGTSTP)\n", "Stopped(SIGTTIN)\n"
		, "Stopped(SIGSTOP)\n"};
	char		*msg;

	msg = messages[2];
	if (job_is_completed(job))
	{
		msg = signal_msg(0);
	}
	else if (job->type == P_AND)
	{
		msg = messages[1];
	}
	else if (job_is_stopped(job))
		msg = messages[1];
	ft_dprintf(STDERR_FILENO, "[%i]%c  %.*s\t\t%s\n", job->jobc_id
	, job->jobc_last, ft_strlen(msg) - 1, msg, job->command);
}

void		job_background_notif(t_job *job)
{
	ft_printf("[%i] %i\n", job->jobc_id, job->pgid);
}

int8_t		do_job_notification(t_core *shell, t_lst *job, int8_t free)
{
	t_job	*ptr;

	if (free)
		update_status(shell);
	while (job)
	{
		ptr = ((t_job*)job->content);
		if (job_is_completed(ptr))
		{
			format_job_info(ptr);
			if (free)
				free_job(&(shell->launched_jobs), job);
			job = shell->launched_jobs;
			continue ;
		}
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			write(STDERR_FILENO, "\n", 1);
			if (ptr->jobc_id == 0)
				attr_jobc_id(shell, ptr);
			format_job_info(ptr);
			ptr->notified = TRUE;
		}
		job = job->next;
	}
	return (SUCCESS);
}
