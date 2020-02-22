/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:42:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/22 19:09:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			builtin_exit(t_core *shell, t_process *process)
{
	int64_t	exit_value;
	int		argc;

	argc = ft_tablen(process->av);
	exit_value = 0;
	if (argc == 1)
		quit_shell(shell, 0, 1);
	if (ft_atol(process->av[1], &exit_value) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "42sh: exit: %s: numeric argument required\n"
				, process->av[1]);
		quit_shell(shell, 255, TRUE);
	}
	else if (argc == 2)
		quit_shell(shell, exit_value & 0xFF, TRUE);
	ft_dprintf(STDERR_FILENO, "42sh: exit: too many arguments\n");
	return (1);
}
