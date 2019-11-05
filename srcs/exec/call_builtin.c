/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/05 02:05:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	static int8_t	(*blt_call[4])(t_core *shell) = {builtin_set
		, builtin_unset, builtin_export, builtin_fc};
	int				ret;

	//redir
	(void)process;
	ret = blt_call[blt](shell);
	//fd restoration
	return (ret);
}
