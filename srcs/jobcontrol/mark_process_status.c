/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/13 17:51:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	background_jobs(t_lst *jobs, pid_t pid, int status)
{
	t_job	*ptr;
	t_lst	*process;

	while (jobs)
	{
		ptr = jobs->content;
		if (ptr->pgid == pid && ptr->type == P_AND)
		{
			process = ptr->process_list;
			while (process)
			{
				((t_process*)process->content)->completed =
				(WIFSIGNALED(status) || WIFEXITED(status)) ? TRUE : FALSE;
				process = process->next;
			}
			return ;
		}
		jobs = jobs->next;
	}
}

int8_t		mark_process_status
	(t_core *shell, t_lst *jobs, pid_t pid, int status)
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
				shell->status = 128 + 18;
				process->stopped = TRUE;
			}
			else
			{
				process->completed = TRUE;
				process->status = (WIFEXITED(status))
					? WEXITSTATUS(status) : WTERMSIG(status);
				status_handler(shell, status);
			}
			update_exit_status(shell);
		}
		else
			background_jobs(jobs, pid, status);
		return (SUCCESS);
	}
	return (FAILURE);
}
