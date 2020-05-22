/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_opt_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:12:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

void			print_hash_map(t_core *shell, enum e_hash fmt)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;

	i = 0;
	if ((map = shell->hash.map) == NULL)
		return ;
	if (fmt == H_DEF)
		ft_dprintf(STDOUT_FILENO, "hits\tcommand\n");
	while (i < shell->hash.size)
	{
		cur_map = map[i++];
		while (cur_map)
		{
			if (fmt == H_DEF)
				ft_dprintf(STDOUT_FILENO, "%4d\t%s\n",
						((t_db *)cur_map->content)->hit,
						((t_db *)cur_map->content)->value);
			if (fmt == H_LISTED)
				ft_dprintf(STDOUT_FILENO, "builtin hash -p %s %s\n",
						((t_db *)cur_map->content)->value,
						((t_db *)cur_map->content)->key);
			cur_map = cur_map->next;
		}
	}
}

static size_t	get_hash_t_pad(const char *key)
{
	size_t	pad;

	pad = ft_strlen(key);
	if (pad > 8)
		pad += 7;
	else if (pad == 8)
		pad += 8;
	else
		pad = 8;
	return (pad);
}

static void		find_hash_sub_map
	(t_process *process, t_lst *map, size_t i, size_t ac)
{
	t_lst	*sub_map;

	sub_map = map;
	while (sub_map)
	{
		if (ft_strequ(process->av[i], ((t_db *)sub_map->content)->key))
		{
			if (ac > 3)
				ft_dprintf(STDOUT_FILENO, "%-*s%s\n",
						get_hash_t_pad(((t_db *)sub_map->content)->key),
						((t_db *)sub_map->content)->key,
						((t_db *)sub_map->content)->value);
			else
				ft_dprintf(STDOUT_FILENO, "%s\n",
						((t_db *)sub_map->content)->value);
			((t_db *)sub_map->content)->hit += 1;
			break ;
		}
		sub_map = sub_map->next;
	}
	if (sub_map == NULL)
		ft_dprintf(STDERR_FILENO,
				"42sh: hash: %s: not found\n", process->av[i]);
}

void			find_hash(t_core *shell, t_process *process, size_t ac)
{
	t_lst	**map;
	size_t	i;

	i = 2;
	map = NULL;
	if (shell->hash.map)
		map = shell->hash.map;
	while (process->av[i])
	{
		shell->hash.value = get_hash(process->av[i], shell->hash.size);
		if (map == NULL || map[shell->hash.value] == NULL)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: hash: %s: not found\n", process->av[i]);
			i++;
			continue;
		}
		find_hash_sub_map(process, map[shell->hash.value], i, ac);
		i++;
	}
}
