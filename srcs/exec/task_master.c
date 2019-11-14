/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:19:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/14 14:07:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	task_master(t_core *shell)
{
	t_lst *job_ptr;

	dprintf(STDERR_FILENO, "??\n");
	if (ft_lstlen(shell->job_list) != 0)
		job_ptr = shell->job_list;
	else
		return (FAILURE);
	dprintf(STDERR_FILENO, "??\n");
	while (job_ptr)
	{
		if (dispatcher(shell, job_ptr) != SUCCESS)
			return (FAILURE);
		job_ptr = job_ptr->next;
	}
	return (SUCCESS);
}
