/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 05:41:09 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:52:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

static int8_t	type(t_core *shell, char *path)
{
	t_process	process;

	ft_bzero(&process, sizeof(t_process));
	process.blt = TRUE;
	if (is_a_blt(path) != FAILURE)
	{
		ft_printf("%s is a shell builtin\n", path);
		return (SUCCESS);
	}
	if ((process.av = (char**)malloc(sizeof(char*) * 2)) == NULL)
		return (FAILURE);
	process.av[0] = path;
	process.av[1] = NULL;
	if (locate_hash(shell, &process) == SUCCESS)
		ft_printf("%s is hashed (%s)\n", path, process.bin);
	else if (get_bin(shell, &process) == SUCCESS
		&& access(process.bin, F_OK | X_OK) == 0)
		ft_printf("%s is %s\n", path, process.bin);
	else
		ft_dprintf(STDERR_FILENO, "42sh: type: %s: not found\n", path);
	ft_strdel(&process.bin);
	free(process.av);
	return (SUCCESS);
}

int8_t			builtin_type(t_core *shell, t_process *process)
{
	size_t	i;
	int8_t	ret;

	i = 1;
	ret = 0;
	while (process->av[i])
	{
		ret = type(shell, process->av[i]);
		i++;
	}
	return ((ret == SUCCESS) ? SUCCESS : 1);
}
