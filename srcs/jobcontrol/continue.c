/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:51:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/03 17:45:27 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	mark_job_as_running(t_job *job)
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

int8_t		continue_job(t_core *shell, t_job *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(shell, shell->launched_jobs, job, TRUE);
	else
		put_job_in_background(shell, job, TRUE);
	return (SUCCESS);
}
