/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:42:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/09 19:28:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_process	*find_process(t_lst *job, pid_t pid)
{
	t_lst	*process;

	while (job != NULL)
	{
		process = ((t_job*)job->content)->process_list;
		while (process)
		{
			if (((t_process*)process->content)->pid == pid)
				return (((t_process*)process->content));
			process = process->next;
		}
		job = job->next;
	}
	return (NULL);
}

u_int8_t	job_is_stopped(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE
				&& ((t_process*)ptr->content)->stopped != TRUE)
			return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}

u_int8_t	job_is_completed(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE)
			return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}
