/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/14 15:56:31 by arsciand         ###   ########.fr       */
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

void	del_hash_key(t_core *shell, t_process *process)
{
	t_lst		*map;
	t_lst		*prev;
	size_t		i;
	u_int32_t	hash_value;

	i = 2;
	if (shell->hash.map == NULL)
		return ;
	while (process->av[i])
	{
		dprintf(STDERR_FILENO, "process->av = |%s|\n", process->av[i]);
		hash_value = get_hash(process->av[i], shell->hash.size);
		map = shell->hash.map[hash_value];
		if (map && ft_strequ(((t_db*)map->content)->key, process->av[i]) == TRUE)
		{
			shell->hash.map[hash_value] = map->next;
			ft_strdel(&((t_db*)map->content)->key);
			ft_strdel(&((t_db*)map->content)->value);
			free(map->content);
			free(map);
			shell->hash.lenght--;
			if (shell->hash.lenght == 0)
			{
				dprintf(STDERR_FILENO, "Hash map erazed\n");
				free(shell->hash.map);
				shell->hash.map = NULL;
			}
			return ;
		}
		while (map && ft_strequ(((t_db*)map->content)->key, process->av[i]) == FALSE)
		{
			prev = map;
			map = map->next;
		}
		if (map == NULL)
		{
			dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", process->av[i]);
			i++;
			continue ;
		}
		prev->next = map->next;
		ft_strdel(&((t_db*)map->content)->key);
		ft_strdel(&((t_db*)map->content)->value);
		free(map->content);
		free(map);
		shell->hash.lenght--;
		i++;
	}
}

int8_t	parse_hash(t_core *shell, int ac, t_process *process)
{
	u_int64_t options;

	options = get_options(ac, process->av, "rlpdt");
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
	if (options & (1ULL << 3))
	{
		if (ac == 2)
			return (SUCCESS);
		del_hash_key(shell, process);
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
