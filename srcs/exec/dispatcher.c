/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/27 13:15:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
static void	debug_process(t_lst *process)
{
	dprintf(STDERR_FILENO, "%i = P_PIPE\n{\n", P_PIPE);
	while (process)
	{
		dprintf(STDERR_FILENO, "+---------------------\n");
		dprintf(STDERR_FILENO, "| %s\n", ((t_process*)process->content)->av[0]);
		dprintf(STDERR_FILENO, "| type = %i\n", ((t_process*)process->content)->type);
		dprintf(STDERR_FILENO, "+---------------------\n");
		if (process->next)
		{
			dprintf(STDERR_FILENO, "           |\n");
			dprintf(STDERR_FILENO, "           V\n");
		}
		process = process->next;
	}
	dprintf(STDERR_FILENO, "}\n");
}*/

int8_t	condition_fulfilled(t_core *shell, int cond)
{
	if (cond != P_ANDIF && cond != P_ORIF)
		return (SUCCESS);
	else if (cond == P_ANDIF && shell->status == 0)
		return (SUCCESS);
	else if (cond == P_ORIF && shell->status != 0)
		return (SUCCESS);
	return (FAILURE);
}

int8_t	dispatcher(t_core *shell, t_lst *jobs)
{
	t_lst	*ptr;
	int		cond;

	ptr = ((t_job*)jobs->content)->process_list;
	cond = 0;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->type == P_PIPE
			&& exec_pipeline(shell, &ptr) != SUCCESS)
			return (FAILURE);
		else if (condition_fulfilled(shell, cond) == SUCCESS)
			exec_process(shell, ptr);
		else
			break ;
		cond = ((t_process*)ptr->content)->type;
		ptr = ptr->next;
	}
	return (SUCCESS);
}
