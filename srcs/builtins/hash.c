/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/03 16:24:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	parse_hash(int ac, char **av)
{
	u_int64_t options;

	options = get_options(ac, av, "r");
	if (options & (1ULL << 63))
	{
		print_usage("hash", options % 128, "[-rl] [-p pathname] [-dt] [name ...]");
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	builtin_hash(t_core *shell, t_process *process)
{
	(void)process;
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;
	int ac;
	int z;

	ac = ft_tablen(process->av);
	z = (ac > 1 && process->av[1][0] != '-' ? 1 : 2);
	dprintf(STDERR_FILENO, "ac = |%d| i = |%d|\n", ac, z);
	if (shell->hash.map == NULL || parse_hash(ac, process->av) != SUCCESS)
		return (FAILURE);
	i = 0;
	map = shell->hash.map;
	cur_map = NULL;
	dprintf(STDOUT_FILENO, "hits    command\n");
	while (i < shell->hash.size)
	{
		cur_map = map[i];
		while (cur_map)
		{
			dprintf(STDOUT_FILENO, "%4d    %s\n",
				((t_db*)cur_map->content)->hit,
				((t_db*)cur_map->content)->value);
			cur_map = cur_map->next;
		}
		i++;
	}
	return (SUCCESS);
}
