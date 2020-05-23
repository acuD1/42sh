/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_jobs_done.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:31:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 20:40:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t	are_jobs_done(t_core *shell, t_lst *jobs)
{
	t_job	*job;

	if (shell->notified != TRUE)
	{
		shell->notified = TRUE;
		while (jobs)
		{
			job = jobs->content;
			if (!(job_is_completed(job)) && job_is_stopped(job))
				return (FALSE);
			jobs = jobs->next;
		}
	}
	return (TRUE);
}
