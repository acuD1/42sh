/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:45:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/17 00:09:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

void	put_job_in_background(t_core *shell, t_job *job, int cont)
{
	if (cont && kill(-job->pgid, SIGCONT) < 0)
		print_and_quit(shell, "42sh: kill (SIGCONT) failed\n");
}
