/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/17 09:03:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	is_a_blt(char *cmd)
{
	static char		*blt_names[8] = {"set", "unset", "export", "hash", "exit", "cd"
		, "echo", "pwd"};
	int				i;

	i = 0;
	while (i < 8)
	{
		if (ft_strcmp(blt_names[i], cmd) == 0)
			return (i);
		i++;
	}
	return (FAILURE);
}

int8_t	call_builtin(t_core *shell, t_lst *process, int blt)
{
	static int8_t	(*blt_call[8])(t_core *shell, t_process *process) = {
		builtin_set, builtin_unset, builtin_export, builtin_hash, builtin_exit, builtin_cd
		, builtin_echo, builtin_pwd};
	int				ret;

	exec_redirs(shell, ((t_process*)process->content)->redir_list);
	ret = blt_call[blt](shell, ((t_process*)process->content));
	close_fds(((t_process*)process->content)->redir_list);
	return (ret);
}
