/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:42:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/22 19:09:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	builtin_exit(t_core *shell, t_process *process)
{
	int64_t	exit_value;
	int		argc;

	argc = ft_tablen(process->av);
	exit_value = 0;
	if (are_jobs_done(shell, shell->launched_jobs) != TRUE)
	{
		write(STDERR_FILENO, "There are stopped jobs.\n", 24);
		return (shell->status);
	}
	if (argc == 1)
		quit_shell(shell, shell->status, 1);
	if (ft_atol(process->av[1], &exit_value) != SUCCESS)
	{
		dprintf(STDERR_FILENO
		, "exit\n42sh: exit: %s: numeric argument required\n", process->av[1]);
		quit_shell(shell, 255, FALSE);
	}
	else if (argc == 2)
		quit_shell(shell, exit_value & 0xFF, TRUE);
	ft_dprintf(STDERR_FILENO, "42sh: exit: too many arguments\n");
	return (1);
}
