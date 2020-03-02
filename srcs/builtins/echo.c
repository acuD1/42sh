/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/16 22:38:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	builtin_echo(t_core *shell, t_process *process)
{
	int		argc;
	int		i;

	(void)shell;
	i = 1;
	argc = ft_tablen(process->av);
	while (i < argc)
	{
		if (write(STDOUT_FILENO, process->av[i], ft_strlen(process->av[i])) < 0)
		{
			ft_dprintf(STDERR_FILENO
			, "42sh: echo: write error: Bad file descriptor\n");
			return (1);
		}
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (SUCCESS);
}
