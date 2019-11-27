/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/27 10:52:41 by arsciand         ###   ########.fr       */
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
	//t_process	*ptr;
	char		**envp;
	int			ret;

	envp = set_envp(shell);
//	ptr = process->content;
	exec_redirs(((t_process*)process->content)->redir_list);
	if (((t_process*)process->content)->bin == NULL)
	{
		dprintf(STDERR_FILENO, "42sh: %s: command not found\n", ((t_process*)process->content)->av[0]);
		// LEAKS faut check avant le fork !
		exit(127);
	}
	if (((t_process*)process->content)->bin && (ret = check_filepath(((t_process*)process->content)->bin)) != SUCCESS)
	{
		ft_perror(((t_process*)process->content)->av[0], ret);
		if (ret == ENOENT)
			exit(127);
		exit(126);
	}
	//print_hash_map(&shell->hash);
	dprintf(STDERR_FILENO, "test\n");
	ret = execve(((t_process*)process->content)->bin, ((t_process*)process->content)->av, envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	ft_tabdel(&envp);
	exit(1);
}
