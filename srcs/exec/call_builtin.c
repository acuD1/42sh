/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 21:35:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	is_a_blt(const char *cmd)
{
	static char	*blt_names[14] = {"set", "unset", "export", "exit", "cd"
	, "echo", "pwd", "type", "fg", "jobs", "bg", "hash", "fc", "test"};
	int8_t		i;

	i = 0;
	while (i < 14)
	{
		if (ft_strcmp(blt_names[i], cmd) == 0)
			return (i);
		i++;
	}
	return (FAILURE);
}

int8_t	call_builtin(t_core *shell, t_process *process, int8_t blt)
{
	static int8_t	(*blt_call[14])(t_core *, t_process *) = {
		builtin_set, builtin_unset, builtin_export, builtin_exit, builtin_cd
		, builtin_echo, builtin_pwd, builtin_type, builtin_fg, builtin_jobs
		, builtin_bg, builtin_hash, builtin_fc, builtin_test};
	int8_t			ret;

	ret = blt_call[blt](shell, process);
	return (ret);
}
