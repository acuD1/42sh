/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:01:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/09 19:27:57 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

void	put_job_in_foreground
	(t_core *shell, t_lst *jobs, t_job *job, u_int8_t cont)
{
	if (tcsetpgrp(shell->terminal, job->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error (foreground 1)\n");
	if (cont)
	{
		mark_job_as_stopped(job, FALSE);
		if (kill(-1 * job->pgid, SIGCONT) < 0)
			print_and_quit(shell, "kill (SIGCONT) error\n");
	}
	wait_for_job(shell, jobs, job);
	if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error (foreground 2)\n");
}
