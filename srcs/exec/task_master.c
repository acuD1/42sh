/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/12 15:37:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	free_job(t_core *shell, t_lst *job)
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
	{
		shell->job_list = job->next;
	}
	free_process_list(&(((t_job*)job->content)->process_list));
	ft_strdel(&(((t_job*)job->content)->command));
	free(job->content);
	free(job);
}

static void	place_job(t_core *shell, t_job *job, int8_t foreground)
{
	if (shell->mode & I_MODE && job_is_completed(job))
		return ;
	if (shell->mode & NOI_MODE)
		wait_for_job(shell, shell->job_list, job);
	else if (foreground == TRUE && !job_is_stopped(job))
		put_job_in_foreground(shell, shell->job_list, job, FALSE);
	else if (foreground == FALSE)
	{
		job->jobc_id = update_jobs(shell->launched_jobs);
		job_background_notif(job);
		update_background_pid(shell);
		put_job_in_background(shell, job, FALSE);
	}
}

int			cond(t_lst *process)
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

static void	handle_background_job(t_core *shell, t_job *job, int foreground)
{
	pid_t	pid;

	pid = -1;
	if (foreground == FALSE && cond(job->process_list) && (pid = fork()) == 0)
	{
		shell->pgid = getpid();
		job->pgid = shell->pgid;
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
		launch_job(shell, job, foreground);
}

int8_t		task_master(t_core *shell)
{
	t_lst	*job;
	t_lst	*next;
	int		foreground;

	job = shell->job_list;
	while (job)
	{
		foreground = (((t_job*)job->content)->type == P_AND) ? FALSE : TRUE;
		next = job->next;
		handle_background_job(shell, job->content, foreground);
		place_job(shell, job->content, foreground);
		if (job_is_completed(job->content))
			free_job(shell, job);
		else
			ft_lstappend(&(shell->launched_jobs), job);
		job = next;
	}
	shell->job_list = NULL;
	return (SUCCESS);
}
