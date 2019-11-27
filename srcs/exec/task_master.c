/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/27 10:59:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	task_master(t_core *shell)
{
	t_lst *job_ptr;

	job_ptr = shell->job_list;
	while (job_ptr)
	{
		if (dispatcher(shell, job_ptr) != SUCCESS)
			return (FAILURE);
		job_ptr = job_ptr->next;
	}
	return (SUCCESS);
}
