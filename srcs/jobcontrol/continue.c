/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:51:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/26 15:58:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
