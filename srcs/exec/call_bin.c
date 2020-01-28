/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/28 19:01:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

/*
**	Function inside the fork where env is created, redirections
*/

static int8_t	check_filepath(char *filepath)
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
	char	**envp;
	int		ret;

	envp = NULL;
	exec_redirs(shell, process->redir_list);
	if (process->bin == NULL)
	{
		if (process->av != NULL)
			dprintf(STDERR_FILENO
				, "42sh: %s: command not found\n", process->av[0]);
		exit(127);
	}
	envp = set_envp(shell);
	if ((ret = check_filepath(process->bin)) != SUCCESS)
	{
		ft_perror(process->av[0], NULL, ret);
		exit((ret == ENOENT) ? 127 : 126);
	}
	ret = execve(process->bin, process->av, envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	ft_tabdel(&envp);
	exit(1);
}
