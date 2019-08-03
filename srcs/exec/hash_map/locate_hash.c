/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:20:26 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/03 11:29:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	locate_hash(t_core *shell, t_hash *hash)
{
	t_lst		**map;
	t_lst		*sub_map;
	size_t		i;

	i = 0;
	if (hash->map == NULL)
		return (FAILURE);
	map = hash->map;
	hash->value = get_hash(shell->tokens[0], hash->size);
	if (map[hash->value] == NULL)
		return (FAILURE);
	sub_map = map[hash->value];
	while (sub_map)
	{
		if (ft_strequ(shell->tokens[0], ((t_db*)(sub_map->content))->key))
		{
			shell->bin = ft_strdup(((t_db*)(sub_map->content))->value);
			((t_db*)(sub_map->content))->hit += 1;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}
