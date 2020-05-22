/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hash_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:01:15 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 18:38:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** This fuctions resize the current hash map with a x2 multiplicator.
** It will almost be never call tho, it's just in case ..
*/

static int8_t	fill_new_hash_map
	(t_core *shell, t_lst **map, t_lst **new_map)
{
	t_lst	*sub_map;
	size_t	i;

	i = 0;
	while (i < shell->hash.size)
	{
		sub_map = map[i];
		while (sub_map)
		{
			shell->hash.value = get_hash(((t_db*)(sub_map->content))->key,
									(shell->hash.size * 2));
			if (!(ft_lstappend(&new_map[shell->hash.value],
					ft_lstnew(fetch_hash_db(&shell->db,
					((t_db*)(sub_map->content))->key,
					((t_db*)(sub_map->content))->value,
					((t_db*)(sub_map->content))->hit), sizeof(t_db)))))
				return (FAILURE);
			sub_map = sub_map->next;
		}
		i++;
	}
	return (SUCCESS);
}

int8_t			resize_hash_map(t_core *shell)
{
	t_lst		**new_map;
	t_lst		**map;
	u_int32_t	tmp_hash_lenght;
	u_int32_t	tmp_hash_size;

	map = shell->hash.map;
	tmp_hash_lenght = shell->hash.lenght;
	tmp_hash_size = shell->hash.size;
	if (!(new_map = ft_memalloc(sizeof(t_lst*) * (shell->hash.size * 2))))
		return (FAILURE);
	if (fill_new_hash_map(shell, map, new_map) != SUCCESS)
		return (FAILURE);
	free_hash_map(&(shell->hash));
	shell->hash.map = new_map;
	shell->hash.size = tmp_hash_size * 2;
	shell->hash.lenght = tmp_hash_lenght;
	return (SUCCESS);
}
