/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:42:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/03 13:31:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			builtin_exit(t_core *shell, t_process *process)
{
	int64_t	exit_value;
	int		argc;

	/*
	argc = ft_tablen(process->av);
	exit_value = 0;
	if (argc == 1)
		quit_shell(shell, 0, 1);
	if (ft_atol(process->av[1], &exit_value) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "bash: exit: %s: numeric argument required\n"
				, process->av[1]);
		quit_shell(shell, 255, 1);
	}
	else if (argc == 2)
		quit_shell(shell, exit_value & 0xFF, 1);
	dprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
	return (FAILURE);
	*/
	(void)process;
	(void)exit_value;
	(void)argc;
	quit_shell(shell, EXIT_SUCCESS, TRUE);
	return (0);
}
