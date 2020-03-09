/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/09 20:00:23 by mpivet-p         ###   ########.fr       */
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
	int		signal;

	signal = (job_is_completed(job)) ? 0 : 7;
	ft_dprintf(STDERR_FILENO, "[%i]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
		, (job_is_stopped(job) && !job_is_completed(job))
		? "Stopped" : signal_msg(signal), job->command);
}

void		job_background_notif(t_job *job)
{
	ft_printf("[%i] %i\n", job->jobc_id, job->pgid);
}

int8_t		do_job_notification(t_core *shell, t_lst *job)
{
	t_job	*ptr;

	update_status(shell);
	while (job)
	{
		ptr = ((t_job*)job->content);
		if (job_is_completed(ptr))
		{
			format_job_info(ptr);
			free_job(&(shell->launched_jobs), job);
			job = shell->launched_jobs;
			continue ;
		}
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			attr_jobc_id(shell, ptr);
			format_job_info(ptr);
			ptr->notified = TRUE;
		}
		job = job->next;
	}
	return (SUCCESS);
}
