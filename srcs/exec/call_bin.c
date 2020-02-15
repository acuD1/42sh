/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/15 16:18:03 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

/*
**	Function inside the fork where env is created, redirections
*/

static int8_t	check_filepath(const char *filepath)
{
	int			ret;

	if ((ret = ft_access(filepath, F_OK | X_OK)) != SUCCESS)
		return (ret);
	if (is_dir(filepath))
		return (EISDIR);
	return (SUCCESS);
}

int8_t			call_bin(t_core *shell, t_process *process)
{
	int		ret;

	if (exec_redirs(shell, process, process->redir_list) != SUCCESS)
		exit (1);
	if (process->bin == NULL)
	{
		if (process->av != NULL)
			dprintf(STDERR_FILENO
				, "42sh: %s: command not found\n", process->av[0]);
		exit(127);
	}
	if ((ret = check_filepath(process->bin)) != SUCCESS)
	{
		ft_perror(process->av[0], NULL, ret);
		exit((ret == ENOENT) ? 127 : 126);
	}
	ret = execve(process->bin, process->av, process->envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	exit (1);
}
