/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/11 19:11:34 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>
#include <unistd.h>

int8_t		mark_process_status
	(t_core *shell, t_lst *jobs, pid_t pid, int status)
{
	t_process	*process;

	if (pid > 0 && (process = find_process(jobs, pid)) && process->pid == pid)
	{
		if (WIFSTOPPED(status))
		{
			process->status = WSTOPSIG(status);
			shell->status =  128 + process->status;
			process->stopped = TRUE;
		}
		else
		{
			process->completed = TRUE;
			process->status = (WIFEXITED(status))
								? WEXITSTATUS(status) : WTERMSIG(status);
			status_handler(shell, process, status);
		}
		return (TRUE);
	}
	return (FALSE);
}
