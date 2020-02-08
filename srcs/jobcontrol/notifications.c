/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/08 05:11:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		update_status(t_core *shell)
{
	pid_t	pid;
	int		status;

	if (!shell->launched_jobs)
		return ;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	printf("cc %i\n", pid);
	while (pid > 0
		&& !mark_process_status(shell, shell->launched_jobs, pid, status))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
}

void		format_job_info(t_job *job)
{
	int		signal;

	signal = (job_is_completed(job)) ? 0 : 7;
	dprintf(STDERR_FILENO, "[%i]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
		, (job_is_stopped(job) && !job_is_completed(job))
		? "Stopped" : signal_msg(signal), job->command);
}

static void	free_job(t_core *shell, t_lst *job)
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
	free_process_list(job->content);
	ft_strdel(&(((t_job*)job->content)->command));
	free(job);
}

void		job_background_notif(t_job *job)
{
	printf("[%i] %i\n", job->jobc_id, job->pgid);
}

int8_t		do_job_notification(t_core *shell, t_lst *job)
{
	t_lst	*jnext;
	t_job	*ptr;

	update_status(shell);
	while (job)
	{
		ptr = ((t_job*)job->content);
		jnext = job->next;
		if (job_is_completed(ptr))
		{
			format_job_info(ptr);
			free_job(shell, job);
			job = shell->launched_jobs;
			ptr = NULL;
		}
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			attr_jobc_id(shell, ptr);
			format_job_info(ptr);
			ptr->notified = TRUE;
		}
		job = jnext;
	}
	return (SUCCESS);
}
