/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/20 22:15:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		mark_process_status(t_core *shell
		, t_lst *jobs, pid_t pid, int status)
{
	t_process	*process;

	if (pid > 0)
	{
		if ((process = find_process(jobs, pid)) && process->pid == pid)
		{
			if (WIFSTOPPED(status))
			{
				printf("\n");
				process->status = 18;
				process->stopped = TRUE;
			}
			else
			{
				process->completed = TRUE;
				process->status = (WIFEXITED(status))
					? WEXITSTATUS(status) : WTERMSIG(status);
				status_handler(shell, status);
			}
		}
		return (SUCCESS);
	}
	else if (pid != 0)
		dprintf(STDERR_FILENO, "42sh: waitpid error (mark_process_status)\n");
	return (FAILURE);
}
