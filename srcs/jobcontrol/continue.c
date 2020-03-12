/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:51:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 20:41:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		continue_job(t_core *shell, t_job *job, int foreground)
{
	mark_job_as_stopped(job, FALSE);
	if (foreground)
		put_job_in_foreground(shell, shell->launched_jobs, job, TRUE);
	else
		put_job_in_background(shell, job, TRUE);
}
