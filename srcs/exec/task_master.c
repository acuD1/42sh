/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/18 19:36:21 by mpivet-p         ###   ########.fr       */
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
	free_process_list(job->content);
	ft_strdel(&(((t_job*)job->content)->command));
	free(job->content);
	free(job);
}

static void	save_job(t_core *shell, t_lst *job)
{
	if (!job_is_completed(job->content))
	{
		ft_lstappend(&(shell->launched_jobs), job);
		return ;
	}
	free_job(shell, job);
	job = NULL;
}

int8_t		task_master(t_core *shell)
{
	t_lst	*job;
	t_lst	*next;

	job = shell->job_list;
	while (job)
	{
		next = job->next;
		launch_job(shell, job->content
				, (((t_job*)job->content)->type != P_AND) ? TRUE : FALSE);
		save_job(shell, job);
		do_job_notification(shell);
		job = next;
	}
	shell->job_list = NULL;
	return (SUCCESS);
}
