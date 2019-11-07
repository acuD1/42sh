/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/07 02:21:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Function inside the fork where env is created, redirections occurs and where
**	
*/

int8_t	call_bin(t_core *shell, t_lst *process)
{
	t_process	*ptr;
	char		**envp;
	int			ret;

	envp = set_envp(shell);
	ptr = process->content;
	//REDIRECTIONS
	if (get_bin(shell, ((t_process*)process->content)) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: %s: command not found\n", ptr->av[0]);
		exit(126);
	}
	ret = execve(ptr->bin, ptr->av, envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	ft_tabdel(&envp);
	exit(1);
}
