/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:17:51 by user42           ###   ########.fr       */
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
	char	*msg;

	if (job_is_completed(job))
	{
		msg = signal_msg(0);
	}
	else
	{
		msg = get_last_stop_status(job);
	}
	ft_dprintf(STDERR_FILENO, "[%i]%c  %.*s\t\t%s\n", job->jobc_id
	, job->jobc_last, ft_strlen(msg) - 1, msg, job->command);
}

void		job_background_notif(t_job *job)
{
	ft_printf("[%i] %i\n", job->jobc_id, job->pgid);
}

void		do_job_notification(t_core *shell, t_lst *job, int8_t free)
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
}
