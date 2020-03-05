/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:51:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/05 21:11:04 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	continue_job(t_core *shell, t_job *job, int foreground)
{
	t_lst	*ptr;

	mark_job_as_stopped(job, FALSE);
	if (foreground)
		put_job_in_foreground(shell, shell->launched_jobs, job, TRUE);
	else
		put_job_in_background(shell, job, TRUE);
	if (job_is_completed(job))
	{
		ptr = shell->launched_jobs;
		while (ptr && ptr->content != job)
			ptr = ptr->next;
		free_job(&(shell->launched_jobs), ptr);
	}
	return (SUCCESS);
}
