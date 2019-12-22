/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:42:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/22 19:09:23 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_job	*find_job(t_lst *ptr, pid_t pgid)
{
	while (ptr != NULL)
	{
		if (((t_job*)ptr->content)->pgid == pgid)
			return (((t_job*)ptr->content));
		ptr = ptr->next;
	}
	return (NULL);
}

int8_t	job_is_stopped(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE
			&& ((t_process*)ptr->content)->stopped != TRUE)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int8_t	job_is_completed(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

void	mark_job_as_running(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		((t_process*)ptr->content)->stopped = FALSE;
		ptr = ptr->next;
	}
	job->notified = FALSE;
}

int8_t	continue_job(t_core *shell, t_job *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(shell, job, TRUE);
	else
		put_job_in_background(shell, job, TRUE);
	return (SUCCESS);
}
