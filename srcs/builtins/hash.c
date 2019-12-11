/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/11 11:27:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_hash_map(t_core *shell, u_int8_t format)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;

	i = 0;
	if (shell->hash.map == NULL)
		return ;
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

int8_t	parse_hash(t_core *shell, int ac, t_process *process)
{
	u_int64_t options;

	options = get_options(ac, process->av, "rlp");
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
	if (options & (1ULL << 15))
	{
		if (ac == 2)
		{
			dprintf(STDERR_FILENO, "42sh: hash: -p: option requires an argument\n");
			print_usage("hash", 0, "[-rl] [-p pathname] [-dt] [name ...]");
			return (FAILURE);
		}
		if (ac == 3)
			return (SUCCESS);
		add_hash_map(shell, process, HASH_PATH);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	builtin_hash(t_core *shell, t_process *process)
{
	int ac;

	ac = ft_tablen(process->av);
	if (parse_hash(shell, ac, process) != SUCCESS)
		return (FAILURE);
	print_hash_map(shell, HASH_DEFAULT);
	return (SUCCESS);
}
