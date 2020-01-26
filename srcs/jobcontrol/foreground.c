/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:01:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/17 00:10:48 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

int8_t	put_job_in_foreground(t_core *shell, t_lst *jobs, t_job *job, int cont)
{
	if (tcsetpgrp(shell->terminal, job->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error (foreground 1)\n");
	if (cont)
	{
		if (tcsetattr(shell->terminal, TCSADRAIN, &(shell->new_t)) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetattr error\n");
		if (kill(-job->pgid, SIGCONT) < 0)
			print_and_quit(shell, "kill (SIGCONT) error\n");
	}
	wait_for_job(shell, jobs, job);
	if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error (foreground 2)\n");
	if (tcsetattr(shell->terminal, TCSADRAIN, &shell->new_t) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetattr error\n");
	return (SUCCESS);
}
