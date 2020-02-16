/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 05:41:09 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/16 22:42:39 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	type(t_core *shell, char *path)
{
	t_process	process;

	ft_bzero(&process, sizeof(t_process));
	process.blt = TRUE;
	if (is_a_blt(path) != FAILURE)
	{
		printf("%s is a shell builtin\n", path);
		return (SUCCESS);
	}
	if ((process.av = (char**)malloc(sizeof(char*) * 2)) == NULL)
		return (FAILURE);
	process.av[0] = path;
	process.av[1] = NULL;
	if (locate_hash(shell, &process) == SUCCESS)
		printf("%s is hashed (%s)\n", path, process.bin);
	else if (get_bin(shell, &process) == SUCCESS
		&& access(process.bin, F_OK | X_OK) == 0)
		printf("%s is %s\n", path, process.bin);
	else
		dprintf(STDERR_FILENO, "42sh: type: %s: not found\n", path);
	ft_strdel(&process.bin);
	free(process.av);
	return (SUCCESS);
}

int8_t			builtin_type(t_core *shell, t_process *process)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (process->av[i])
	{
		ret = type(shell, process->av[i]);
		i++;
	}
	return ((ret == SUCCESS) ? SUCCESS : 1);
}
