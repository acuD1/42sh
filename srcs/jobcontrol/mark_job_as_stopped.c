/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_job_as_stopped.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:04:30 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 20:36:43 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	mark_job_as_stopped(t_job *job, int8_t stopped)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		((t_process*)ptr->content)->stopped = stopped;
		ptr = ptr->next;
	}
	job->notified = FALSE;
}
