/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hash_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:01:15 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/03 11:37:16 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/* This fuctions resize the current hash map with a x2 multiplicator.
** It will almost be never call tho, it's just in case ..
*/

static void	fill_new_hash_map
	(t_core *shell, t_hash *hash, t_lst **map, t_lst **new_map)
{
	t_lst		*sub_map;
	size_t		i;

	i = 0;
	while (i < hash->size)
	{
		sub_map = map[i];
		while (sub_map)
		{
			hash->lenght++;
			hash->value = get_hash(((t_db*)(sub_map->content))->key,
									(hash->size * 2));
			ft_lstappend(&new_map[hash->value],
				ft_lstnew(fetch_hash_db(&shell->db,
					((t_db*)(sub_map->content))->key,
					((t_db*)(sub_map->content))->value), sizeof(t_db)));
			sub_map = sub_map->next;
		}
		i++;
	}
}

int8_t		resize_hash_map(t_core *shell, t_hash *hash)
{
	t_lst		**new_map;
	t_lst		**map;

	map = hash->map;

	hash->lenght = 0;
	if (!(new_map = ft_memalloc(sizeof(t_lst*) * (hash->size * 2))))
		return (FAILURE);
	fill_new_hash_map(shell, hash, map, new_map);
	free_hash_map(hash);
	hash->map = new_map;
	hash->size *= 2;
	return (SUCCESS);
}
