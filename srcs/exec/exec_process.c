/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/11 23:38:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
 **	exec_process takes for parameter t_lst *env for now because we can set
 **	a temporary environnement if we use the env builtin.
 */

int8_t	exec_process(t_core *shell, t_lst *process)
{
	t_process	*ptr;
	pid_t		pid;
	int			status;
	int			blt;

	status = 0;
	ptr = ((t_process*)process->content);
	expansion(shell, ptr);
	if (ptr->av)
	{
		ft_printtab(ptr->av);
		if ((blt = is_a_blt(ptr->av[0])) != FAILURE)
		{
			shell->status = call_builtin(shell, process, blt);
			return (SUCCESS);
		}
		get_bin(shell, ptr);
	}
	if ((pid = fork()) < 0)
	{
		dprintf(STDERR_FILENO, "42sh: fork error\n");
		return (FAILURE);
	}
	else if (pid == 0)
		call_bin(shell, process);
	ptr->pid = pid;
	ft_strdel(&(ptr->bin));
	shell->running_process = process;
	if (waitpid(pid, &shell->status, WUNTRACED | WCONTINUED) != pid)
	{
		dprintf(STDERR_FILENO, "42sh: waitpid error\n");
		return (FAILURE);
	}
	shell->running_process = NULL;
	status_handler(shell, shell->status);
	return (SUCCESS);
}
