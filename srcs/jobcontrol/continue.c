/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:51:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/12 14:23:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	continue_job(t_core *shell, t_job *job, int foreground)
{
	mark_job_as_stopped(job, FALSE);
	if (foreground)
		put_job_in_foreground(shell, shell->launched_jobs, job, TRUE);
	else
		put_job_in_background(shell, job, TRUE);
	return (SUCCESS);
}
