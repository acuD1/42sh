/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_stop_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:10:07 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/18 15:10:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

static char	*get_short_status(int status)
{
	static char	*msg[4] = {"Stopped(SIGSTOP)\n", "Stopped(SIGTSTP)\n"
		, "Stopped(SIGTTIN)\n", "Stopped(SIGTTOU)\n"};

	status = WSTOPSIG(status);
	if (status == SIGSTOP)
		return (msg[0]);
	if (status == SIGTSTP)
		return (msg[1]);
	if (status == SIGTTIN)
		return (msg[2]);
	return (msg[3]);
}

char		*get_last_stop_status(t_job *job)
{
	static char	done[] = "Done\n";
	t_process	*process;
	t_lst		*ptr;

	ptr = job->process_list;
	if (!job_is_completed(job))
	{
		while (ptr)
		{
			process = ptr->content;
			if (WIFSTOPPED(process->status))
				return (get_short_status(process->status));
			ptr = ptr->next;
		}
	}
	return (done);
}
