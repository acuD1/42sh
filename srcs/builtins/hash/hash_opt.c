/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:05:40 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>

int8_t	hash_l(t_core *shell, t_process *process, size_t ac)
{
	(void)process;
	(void)ac;
	print_hash_map(shell, H_LISTED);
	return (SUCCESS);
}

int8_t	hash_r(t_core *shell, t_process *process, size_t ac)
{
	(void)process;
	(void)ac;
	free_hash_map(&shell->hash);
	return (SUCCESS);
}

int8_t	hash_p(t_core *shell, t_process *process, size_t ac)
{
	size_t	i;

	i = 3;
	if (ac == 2)
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: hash: -p: option requires an argument\n");
		print_usage("hash", 0, "[-rl] [-p pathname] [-dt] [name ...]");
		return (SUCCESS);
	}
	if (ac == 3)
		return (FAILURE);
	if (is_a_dir(process->av[2]) == EISDIR)
	{
		while (process->av[i])
		{
			ft_dprintf(STDERR_FILENO, "42sh: hash: %s: Is a directoy\n",
					process->av[2]);
			i++;
		}
		return (SUCCESS);
	}
	hash_dispatcher(shell, process, H_PATH);
	return (SUCCESS);
}

int8_t	hash_d(t_core *shell, t_process *process, size_t ac)
{
	size_t	i;

	i = 2;
	if (ac == 2)
		return (FAILURE);
	while (process->av[i])
		hash_key_remover(shell, process->av[i++]);
	return (SUCCESS);
}

int8_t	hash_t(t_core *shell, t_process *process, size_t ac)
{
	if (ac > 2)
		find_hash(shell, process, ac);
	else
		ft_dprintf(STDERR_FILENO,
			"42sh: hash: -t: option requires an argument\n");
	return (SUCCESS);
}
