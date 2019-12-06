/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/06 10:07:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_hash_map(t_core *shell, u_int8_t format)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;

	i = 0;
	map = shell->hash.map;
	cur_map = NULL;
	if (format & HASH_DEFAULT)
		dprintf(STDOUT_FILENO, "hits    command\n");
	while (i < shell->hash.size)
	{
		cur_map = map[i];
		while (cur_map)
		{
			if (format & HASH_DEFAULT)
				dprintf(STDOUT_FILENO, "%4d    %s\n",
					((t_db*)cur_map->content)->hit,
					((t_db*)cur_map->content)->value);
			if (format & HASH_LISTED)
				dprintf(STDOUT_FILENO, "builtin hash -p %s %s\n",
					((t_db*)cur_map->content)->value,
					((t_db*)cur_map->content)->key);
			cur_map = cur_map->next;
		}
		i++;
	}
}

int8_t	parse_hash(t_core *shell, int ac, char **av)
{
	u_int64_t options;

	options = get_options(ac, av, "rl");
	if (options & (1ULL << 63))
	{
		print_usage("hash", options % 128, "[-rl] [-p pathname] [-dt] [name ...]");
		return (FAILURE);
	}
	if (options & (1ULL << 11))
	{
		print_hash_map(shell, HASH_LISTED);
		return (FAILURE);
	}
	if (options & (1ULL << 17))
	{
		free_hash_map(&shell->hash);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	builtin_hash(t_core *shell, t_process *process)
{
	int ac;
	int z;

	ac = ft_tablen(process->av);
	z = (ac > 1 && process->av[1][0] != '-' ? 1 : 2);
	if (shell->hash.map == NULL || parse_hash(shell, ac, process->av) != SUCCESS)
		return (FAILURE);
	print_hash_map(shell, HASH_DEFAULT);
	return (SUCCESS);
}
