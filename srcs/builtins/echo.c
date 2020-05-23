/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int8_t	builtin_echo(t_core *shell, t_process *process)
{
	size_t	argc;
	size_t	i;

	(void)shell;
	i = 1;
	if (write(STDOUT_FILENO, NULL, 0) < 0)
	{
		ft_dprintf(STDERR_FILENO
		, "42sh: echo: write error: Bad file descriptor\n");
		return (1);
	}
	argc = ft_tablen(process->av);
	while (i < argc)
	{
		write(STDOUT_FILENO, process->av[i], ft_strlen(process->av[i]));
		i++;
		if (i < argc)
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
