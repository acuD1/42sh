/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:42:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/18 19:44:32 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_process	*find_process(t_lst *job, pid_t pid)
{
	t_lst *process;

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

t_job		*find_job(t_lst *job, pid_t pgid)
{
	while (job != NULL)
	{
		if (((t_job*)job->content)->pgid == pgid)
			return (((t_job*)job->content));
		job = job->next;
	}
	return (NULL);
}

int8_t		job_is_stopped(t_job *job)
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

int8_t		job_is_completed(t_job *job)
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

void		debug_job(t_job *job)
{
	t_lst *ptr;

	ptr = job->process_list;
	printf(" ** JOB **\n");
	while (ptr)
	{
		printf("[stopped] = %i || [completed] = %i\n====\n"
		, ((t_process*)ptr->content)->stopped
		, ((t_process*)ptr->content)->completed);
		ptr = ptr->next;
	}
}
