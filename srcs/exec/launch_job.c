/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/11 22:25:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <sys/wait.h>

static void	setup_pipes(t_process *process, t_lst *ptr)
{
	t_process	*next;
	int			pipes[2];

	if (process->type == P_PIPE)
	{
		pipe(pipes);
		next = ptr->content;
		process->pipe[1] = pipes[1];
		process->close[1] = pipes[0];
		next->pipe[0] = pipes[0];
		next->close[0] = pipes[1];
	}
}

static void	condition_fulfilled(t_lst *process)
{
	t_process	*ptr;
	int			cond;

	ptr = ((t_process *)process->content);
	cond = ptr->type;
	if (cond != P_ANDIF && cond != P_ORIF)
		return ;
	else if (cond == P_ANDIF
	&& get_signal(ptr->status) == 0 && WEXITSTATUS(ptr->status) == 0)
		return ;
	else if (cond == P_ORIF
	&& (get_signal(ptr->status) != 0 || WEXITSTATUS(ptr->status) != 0))
		return ;
	while (process && (ptr = ((t_process *)process->content))
	&& (ptr->type == (enum e_pstate)cond || ptr->type == P_PIPE))
	{
		((t_process *)process->next->content)->completed = TRUE;
		process = process->next;
	}
}

static void	clear_process(t_job *job, t_lst **ptr)
{
	t_lst	*prev;

	prev = job->process_list;
	if (((t_process*)(*ptr)->content)->completed == TRUE)
	{
		while (prev != *ptr)
			prev = prev->next;	
		if (prev == job->process_list)
			job->process_list = (*ptr)->next;
		else
			prev->next = (*ptr)->next;
	}
	*ptr = (*ptr)->next;
}

void		launch_job(t_core *shell, t_job *job, int foreground)
{
	t_process	*ptr;
	t_lst		*process;

	process = job->process_list;
	while (process && (ptr = ((t_process *)process->content)))
	{
		ptr->stopped = (foreground == TRUE) ? FALSE : TRUE;
		if (ptr->completed == FALSE)
		{
			setup_pipes(ptr, process->next);
			expansion(shell, ptr);
			if (ptr->completed == FALSE)
			{
				launch_blt(shell, ptr);
				if (ptr->completed == FALSE)
					exec_process(shell, job, ptr);
			}
			update_exit_status(shell);
			condition_fulfilled(process);
		}
		clear_process(job, &process);
	}
}
