/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/19 22:54:31 by mpivet-p         ###   ########.fr       */
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
		if (job_is_completed(job->content))
			free_job(shell, job);
		else
			ft_lstappend(&(shell->launched_jobs), job);
		job = next;
	}
	shell->job_list = NULL;
	return (SUCCESS);
}
