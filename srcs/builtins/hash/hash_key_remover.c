/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_key_remover.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:55:30 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/10 20:54:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	hash_key_remover_finder
	(t_core *shell, char *process, t_lst *map, t_lst *prev)
{
	while (map && ft_strequ(((t_db *)map->content)->key, process) == FALSE)
	{
		prev = map;
		if ((map = map->next) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", process);
			return ;
		}
	}
	prev->next = map->next;
	free_hash_key(&shell->hash, map);
}

void		hash_key_remover(t_core *shell, char *process)
{
	t_lst		*map;
	t_lst		*prev;
	u_int32_t	hash_value;

	prev = NULL;
	if (shell->hash.map == NULL || process == NULL)
		return ;
	hash_value = get_hash(process, shell->hash.size);
	if ((map = shell->hash.map[hash_value]) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", process);
		return ;
	}
	if (map && ft_strequ(((t_db *)map->content)->key, process) == TRUE)
	{
		shell->hash.map[hash_value] = map->next;
		free_hash_key(&shell->hash, map);
		return ;
	}
	hash_key_remover_finder(shell, process, map, prev);
}
