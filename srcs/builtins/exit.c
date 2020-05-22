/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:42:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int8_t	builtin_exit(t_core *shell, t_process *process)
{
	int64_t	exit_value;
	size_t	argc;

	argc = ft_tablen(process->av);
	exit_value = 0;
	if (are_jobs_done(shell, shell->launched_jobs) != TRUE)
	{
		write(STDERR_FILENO, "exit\nThere are stopped jobs.\n", 29);
		return (1);
	}
	if (argc == 1)
		quit_shell(shell, shell->status, 1);
	if (ft_atol(process->av[1], &exit_value) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO
		, "exit\n42sh: exit: %s: numeric argument required\n", process->av[1]);
		quit_shell(shell, 2, FALSE);
	}
	else if (argc == 2)
		quit_shell(shell, exit_value & 0xFF, TRUE);
	ft_dprintf(STDERR_FILENO, "42sh: exit: too many arguments\n");
	return (1);
}
