/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/28 19:12:19 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	task_master(t_core *shell)
{
	t_lst *job;

	job = shell->job_list;
	while (job)
	{
		printf("[ %i ]\n", ((t_job*)job->content)->type);
		if (dispatcher(shell, job) != SUCCESS)
			return (FAILURE);
		job = job->next;
	}
	return (SUCCESS);
}
