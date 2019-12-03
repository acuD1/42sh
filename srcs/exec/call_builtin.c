/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/01 15:00:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/* Need FC Final

int8_t	is_a_blt(char *cmd)
{
	static char		*blt_names[BLT_NUMBER] = {"set", "unset", "export", "fc"};
	int				i;

	i = 0;
	while (i < BLT_NUMBER)
	{
		if (ft_strcmp(blt_names[i], cmd) == 0)
			return (i);
		i++;
	}
	return (FAILURE);
}

int8_t	call_builtin(t_core *shell, t_lst *process, int blt)
{
	static int8_t	(*blt_call[4])(t_core *shell, t_process *process) = {
		builtin_set, builtin_unset, builtin_export, builtin_fc};
	int				ret;

	exec_redirs(((t_process*)process->content)->redir_list);
	ret = blt_call[blt](shell, ((t_process*)process->content));
	close_fds(((t_process*)process->content)->redir_list);
	return (ret);
}
*/

int8_t	is_a_blt(char *cmd)
{
	static char		*blt_names[5] = {"set", "unset", "export", "exit", "hash"}; //echo, pwd, cd,
	int				i;

	i = 0;
	while (i < 5)
	{
		if (ft_strcmp(blt_names[i], cmd) == 0)
			return (i);
		i++;
	}
	return (FAILURE);
}

int8_t	call_builtin(t_core *shell, t_lst *process, int blt)
{
	static int8_t	(*blt_call[5])(t_core *shell, t_process *process) = {
		builtin_set, builtin_unset, builtin_export, builtin_exit, builtin_hash};
	int				ret;

	exec_redirs(((t_process*)process->content)->redir_list);
	ret = blt_call[blt](shell, ((t_process*)process->content));
	close_fds(((t_process*)process->content)->redir_list);
	return (ret);
}
