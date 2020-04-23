/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 15:25:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	t_process		*ptr;
	enum e_pstate	cond;

	ptr = ((t_process *)process->content);
	cond = ptr->type;
	if (cond != P_ANDIF && cond != P_ORIF)
		return ;
	else if (cond == P_ANDIF && ptr->status == 0)
		return ;
	else if (cond == P_ORIF && ptr->status != 0)
		return ;
	while (process && (ptr = ((t_process *)process->content))
	&& (ptr->type == (enum e_pstate)cond || ptr->type == P_PIPE))
	{
		((t_process *)process->next->content)->completed = TRUE;
		process = process->next;
	}
}

static void	init_process_list(t_lst *process)
{
	t_process *ptr;

	while (process)
	{
		ptr = process->content;
		ptr->pipe[0] = STDIN_FILENO;
		ptr->pipe[1] = STDOUT_FILENO;
		ptr->close[0] = -1;
		ptr->close[1] = -1;
		process = process->next;
	}
}

void		launch_job(t_core *shell, t_job *job, int foreground)
{
	t_process	*ptr;
	t_lst		*process;

	process = job->process_list;
	init_process_list(process);
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
		process = process->next;
	}
}
