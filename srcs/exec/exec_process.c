/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/18 12:36:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	exec_process takes for parameter t_lst *env for now because we can set
**	a temporary environnement if we use the env builtin.
*/

int8_t	exec_process(t_core *shell, t_lst *process)
{
	pid_t	pid;
	int		status;
	int		blt;

	status = 0;
	//EXPANSION
	if ((blt = is_a_blt(((t_process*)process->content)->av[0])) != FAILURE)
	{
		shell->status = call_builtin(shell, process, blt);
		return (SUCCESS);
	}
	if ((pid = fork()) < 0)
		return (exec_handler(shell, FORK_ERROR)); //NEED REWORK
	else if (pid == 0)
		call_bin(shell, process);
	if (waitpid(pid, &shell->status, WCONTINUED) != pid)
	{
		dprintf(STDERR_FILENO, "42sh: waitpid error\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
