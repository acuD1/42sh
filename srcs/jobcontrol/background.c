/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:45:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/22 19:03:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

void	put_job_in_background(t_core *shell, t_job *job, int cont)
{
	/* Send the job a continue signal, if necessary.	*/
	if (cont && kill (- job->pgid, SIGCONT) < 0)
		print_and_quit(shell, "42sh: kill (SIGCONT) failed\n");
}
