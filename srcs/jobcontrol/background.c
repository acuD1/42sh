/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:45:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 20:42:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

void	put_job_in_background(t_core *shell, t_job *job, u_int8_t cont)
{
	job->jobc_last = '+';
	update_background_pid(shell);
	if (cont && kill(-1 * job->pgid, SIGCONT) < 0)
		print_and_quit(shell, "42sh: kill (SIGCONT) failed\n");
}
