/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:58:44 by user42           ###   ########.fr       */
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
		process->status = status;
		if (WIFSTOPPED(status))
			process->stopped = TRUE;
		else
			process->completed = TRUE;
		status_handler(shell, process);
		return (TRUE);
	}
	return (FALSE);
}
