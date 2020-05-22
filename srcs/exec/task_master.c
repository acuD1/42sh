/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:22:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void		place_job(t_core *shell, t_job *job, int8_t foreground)
{
	if (shell->is_interactive && job_is_completed(job))
		return ;
	if (!(shell->is_interactive))
		wait_for_job(shell, shell->job_list, job);
	else if (foreground == FALSE)
	{
		job->jobc_id = update_jobs(shell->launched_jobs);
		job_background_notif(job);
		update_background_pid(shell);
		put_job_in_background(shell, job, FALSE);
	}
}

int				cond(t_lst *process)
{
	while (process)
	{
		if (((t_process*)process->content)->type == P_ANDIF
			|| ((t_process*)process->content)->type == P_ORIF)
			return (TRUE);
		process = process->next;
	}
	return (FALSE);
}

static int8_t	handle_background_job(t_core *shell, t_job *job, int foreground)
{
	pid_t	pid;

	pid = -1;
	if (foreground == FALSE && cond(job->process_list) && (pid = fork()) == 0)
	{
		shell->pgid = getpid();
		job->pgid = shell->pgid;
		shell->is_interactive = FALSE;
		if (setpgid(shell->pgid, shell->pgid) < 0)
			exit(1);
		launch_job(shell, job, foreground);
		exit(0);
	}
	else if (foreground == FALSE && pid > 0)
	{
		mark_job_as_stopped(job, TRUE);
		job->notified = TRUE;
		job->pgid = pid;
		shell->status = 0;
	}
	else
		return (launch_job(shell, job, foreground));
	return (SUCCESS);
}

void			task_master(t_core *shell)
{
	int8_t	foreground;
	t_lst	*job;
	t_lst	*next;

	job = shell->job_list;
	while (job)
	{
		foreground = ((t_job*)job->content)->type == P_AND ? FALSE : TRUE;
		next = job->next;
		if (handle_background_job(shell, job->content, foreground) == 1)
			break ;
		place_job(shell, job->content, foreground);
		if (job_is_completed(job->content))
			free_job(&(shell->job_list), job);
		else
		{
			shell->job_list = job->next;
			job->next = NULL;
			ft_lstappend(&(shell->launched_jobs), job);
		}
		job = next;
	}
	ft_freejoblist(&(shell->job_list));
}
