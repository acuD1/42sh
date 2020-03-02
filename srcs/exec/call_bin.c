/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/19 00:26:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

/*
**	Function inside the fork where env is created, redirections
*/

static int8_t	check_filepath(t_process *process)
{
	int			ret;

	ret = 0;
	if (process->av == NULL)
		return (ret);
	if (process->bin == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s: command not found\n", process->av[0]);
		ret = 127;
	}
	else if ((ret = ft_access(process->bin, F_OK | X_OK)) != SUCCESS)
		ft_perror(process->bin, NULL, ret);
	else if (is_dir(process->bin))
		ft_perror(process->av[0], NULL, EISDIR);
	else
		return (0);
	return ((ret == 127) ? 127 : 126);
}

int8_t			call_bin(t_core *shell, t_process *process)
{
	int		ret;

	ret = 0;
	if (exec_redirs(shell, process, process->redir_list) != SUCCESS)
		exit(1);
	if (process->bin == NULL)
	{
		if (process->av != NULL)
			ft_dprintf(STDERR_FILENO
				, "42sh: %s: command not found\n", process->av[0]);
		exit(127);
	}
	if ((ret = check_filepath(process)) == 0)
	{
		ret = execve(process->bin, process->av, process->envp);
		ft_dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
		exit(1);
	}
	exit(ret);
}
