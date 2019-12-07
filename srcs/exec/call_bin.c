/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/07 21:06:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

/*
**	Function inside the fork where env is created, redirections occurs and where
**
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
int8_t	call_bin(t_core *shell, t_lst *process)
{
	t_process	*ptr;
	char		**envp;
	int			ret;

	envp = set_envp(shell);
	ptr = process->content; //Shortcut to ((t_process*)proces->content)
	exec_redirs(ptr->redir_list);
	if (ptr->bin == NULL)
	{
		dprintf(STDERR_FILENO, "42sh: %s: command not found\n", ptr->av[0]);
		exit(127);
	}
	if ((ret = check_filepath(ptr->bin)) != SUCCESS)
	{
		ft_perror(ptr->av[0], NULL, ret);
		exit((ret == ENOENT) ? 127: 126);
	}
	ret = execve(ptr->bin, ptr->av, envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	ft_tabdel(&envp);
	exit(1);
}
