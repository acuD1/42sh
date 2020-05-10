/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

/*
**	Function inside the fork where env is created, redirections
*/

static int8_t	check_filepath(t_process *process)
{
	int8_t	ret;

	ret = 0;
	if (process->av == NULL)
		return (ret);
	if (process->bin == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: %s: command not found\n", process->av[0]);
		ret = 127;
	}
	else if ((ret = ft_access(process->bin, F_OK | X_OK)) != SUCCESS)
		ft_perror(process->bin, NULL, ret);
	else if (is_dir(process->bin))
		ft_perror(process->av[0], NULL, EISDIR);
	else
		return (0);
	return ((ret == 127 || ret == 2) ? 127 : 126);
}

void			call_bin(t_core *shell, t_process *process)
{
	int8_t	blt;
	int		ret;

	ret = 0;
	if (exec_redirs(shell, process, process->redir_list) != SUCCESS)
		exit(1);
	if (process->av && (blt = is_a_blt(process->av[0])) != FAILURE)
	{
		shell->is_interactive = FALSE;
		exit(call_builtin(shell, process, blt));
	}
	if (process->bin == NULL)
	{
		if (process->av != NULL)
			ft_dprintf(STDERR_FILENO
				, "42sh: %s: command not found\n", process->av[0]);
		exit(127);
	}
	if ((ret = (int)check_filepath(process)) == 0)
	{
		ret = execve(process->bin, process->av, process->envp);
		ft_dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
		exit(1);
	}
	exit(ret);
}
