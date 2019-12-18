/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:59:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/04 17:40:56 by mpivet-p         ###   ########.fr       */
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
		ft_putstr(process->av[i]);
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (SUCCESS);
}
