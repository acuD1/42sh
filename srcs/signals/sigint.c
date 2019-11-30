/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/30 10:09:11 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

/* Peut etre un truc tricky a gerer (wait apres chaque kill ?) */

void	kill_processes(int signum, t_core *shell)
{
	t_lst	*ptr;

	ptr = shell->running_process->next;
	kill(((t_process*)shell->running_process->content)->pid, signum);
	if (ptr && ((t_process*)ptr->content)->type == P_PIPE)
	{
		while (ptr && ((t_process*)ptr->content)->type == P_PIPE)
		{
			kill(((t_process*)ptr->content)->pid, signum);
			ptr = ptr->next;
		}
		kill(((t_process*)ptr->content)->pid, signum);
	}
	shell->running_process = NULL;
}

void	sigint_handler(int signum)
{
	t_core	*shell;

	(void)signum;
	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	if (shell->running_process != NULL)
		kill_processes(signum, shell);
}
