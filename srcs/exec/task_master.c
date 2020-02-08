/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/08 02:46:08 by mpivet-p         ###   ########.fr       */
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

static void	cond_test(t_core *shell, t_job *job)
{
	pid_t	pid;
	int		foreground;

	foreground = (job->type != P_AND) ? TRUE : FALSE;
	if (foreground == FALSE && (pid = fork()) == 0)
	{
		shell->pgid = getpid();
		job->pgid = shell->pgid;
		if (setpgid(shell->pgid, shell->pgid) < 0)
			print_and_quit(shell, "42sh: Couldn't put the shell in its own process group\n");
		launch_job(shell, job, foreground);
		exit(1);
	}
	else if (foreground == FALSE)
	{
		job->pgid = pid;
		job->jobc_id = update_jobs(shell->launched_jobs);
		job_background_notif(job);
		put_job_in_background(shell, job, FALSE);
		shell->status = 0;
	}
	else
		launch_job(shell, job, foreground);
}

int8_t		task_master(t_core *shell)
{
	t_lst	*job;
	t_lst	*next;

	job = shell->job_list;
	while (job)
	{
		next = job->next;
		cond_test(shell, job->content);
		if (job_is_completed(job->content))
		{
			printf("DONE\n");
			free_job(shell, job);
		}
		else
			ft_lstappend(&(shell->launched_jobs), job);
		do_job_notification(shell, shell->launched_jobs);
		job = next;
	}
	shell->job_list = NULL;
	return (SUCCESS);
}
