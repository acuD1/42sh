/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:01:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/22 19:02:28 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

int8_t	put_job_in_foreground(t_core *shell, t_job *job, int cont)
{
	/* Put the job into the foreground.	*/
	if (tcsetpgrp(shell->terminal, job->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error\n");

	/* Send the job a continue signal, if necessary.	*/
	if (cont)
	{
		if (tcsetattr(shell->terminal, TCSADRAIN, &(job->tmodes)) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetattr error\n");
		if (kill(- job->pgid, SIGCONT) < 0)
			print_and_quit(shell, "kill (SIGCONT) error\n");
	}

	/* Wait for it to report */
//	wait_for_job(job);

	/* Put the shell back in the foreground */
	if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error\n");

	/* Restore the shell’s terminal modes */
	tcgetattr(shell->terminal, &job->tmodes);
	tcsetattr(shell->terminal, TCSADRAIN, &shell->new_t);
	return (SUCCESS);
}
