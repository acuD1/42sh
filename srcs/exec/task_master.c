/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/04 18:31:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	task_master(t_core *shell)
{
	t_lst *job;

	job = shell->job_list;
	while (job)
	{
		//printf("[ %i ]\n", ((t_job*)job->content)->type);
		launch_job(shell, job->content);
		job = job->next;
	}
	return (SUCCESS);
}
