/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/01 18:57:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Made for tests. ? .
*/

int8_t	is_a_blt(char	*cmd)
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

int8_t	exec_builtin(t_core *shell, t_lst *process)
{
	static int8_t	(*blt_call[4])(t_core *shell) = {builtin_set
		, builtin_unset, builtin_export, builtin_fc};
	int				blt;

	blt = is_a_blt(process->av[0]);
	return (blt_call[blt](shell));
}
