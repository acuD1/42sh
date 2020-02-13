/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:58:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/13 22:36:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Function inside the fork where env is created, redirections
*/

int8_t			call_bin(t_core *shell, t_process *process)
{
	int		ret;

	(void)shell;
	ret = execve(process->bin, process->av, process->envp);
	dprintf(STDERR_FILENO, "42sh: excve failure [%i]\n", ret);
	exit(1);
}
