/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:54:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/18 16:47:51 by fcatusse         ###   ########.fr       */
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
} */

int8_t	dispatcher(t_core *shell, t_lst *jobs)
{
	t_lst	*ptr;
	int		status;

	ptr = ((t_job*)jobs->content)->process_list;
	status = 0;
	//debug_process(ptr);
	while (ptr != NULL)
	{
		if ((!(*(t_process*)ptr->content).av))
		{
			ptr = ptr->next;
		}
		else if (((t_process*)ptr->content)->type == P_PIPE)
		{
			if (exec_pipeline(shell, &ptr) != SUCCESS)
			{
				printf("ERROR\n");
				return (FAILURE);
			}
		}
		else if (((t_process*)ptr->content)->type == P_ASSIGN)
		{
			printf("FAUT GERER CA CEST BIEN BEAU DE STOCKER DANS UNE LST MAIS APRES ?\n");
			ptr = ptr->next;
		}
		else
		{
			if (is_expansion(((t_process*)ptr->content)->type))
			{
				if (!expansion(shell, (t_process*)ptr->content))
					break;
			}	
			exec_process(shell, ptr);
			ptr = ptr->next;
		}
	}
	return (SUCCESS);
}
