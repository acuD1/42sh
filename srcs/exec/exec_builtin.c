/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/22 15:04:53 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Made for tests. ? .
*/

int8_t	exec_builtin(t_core *shell)
{
	static char		*blt_names[5] = {"set", "unset", "export", "fc", NULL};
	static int8_t	(*blt_call[4])(t_core *shell) = {builtin_set
		, builtin_unset, builtin_export, builtin_fc};
	char			**ret;
	int				blt;

	blt = 0;
	if ((ret = ft_tabchr(blt_names, shell->tokens[0])) == NULL
			|| (blt = ret - blt_names) < 0)
	{
		return (FAILURE);
	}
	return (blt_call[blt](shell));
}
