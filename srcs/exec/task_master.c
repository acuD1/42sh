/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/08 22:39:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
void	remove_completed_jobs(t_lst **jobs)
{
	t_lst	*ptr;
	t_lst	*next;

	ptr = *jobs;
	while (ptr)
	{
		next = ptr->next;
		if (job_is_completed(ptr->content)
			free_job(shell, ptr);
		ptr = next;
	}
}*/

int8_t	task_master(t_core *shell)
{
	t_lst *job;

	job = shell->job_list;
	while (job)
	{
		ft_lstappend(&(shell->launched_jobs), job);
		launch_job(shell, job->content);
		job = job->next;
	}
	shell->job_list = NULL;
	return (SUCCESS);
}
