/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:20:26 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/18 08:09:33 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	locate_hash(t_core *shell, t_process *process)
{
	t_lst		**map;
	t_lst		*sub_map;
	t_db		*db;

	if (shell->hash.map == NULL)
		return (FAILURE);
	map = shell->hash.map;
	shell->hash.value = get_hash(process->av[0], shell->hash.size);
	if (map[shell->hash.value] == NULL)
		return (FAILURE);
	sub_map = map[shell->hash.value];
	while (sub_map)
	{
		db = sub_map->content;
		if (ft_strequ(process->av[0], db->key))
		{
			if (ft_access(db->value, F_OK | X_OK) != SUCCESS)
			{
				if ((db->value[0] == '.' && db->value[1] == '/'
					&& db->value[2] != 0))
					db->hit += 1;
				else
					del_hash_key(shell, process->av[0]);
				return (SUCCESS);
			}
			process->bin = ft_strdup(db->value);
			db->hit += 1;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}


/*Rework del_hash_key to have only one char in argument so locate hash delete this key aswell.
*/
