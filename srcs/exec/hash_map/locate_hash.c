/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:20:26 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/15 12:50:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	locate_hash(t_core *shell, t_process *process)
{
	t_lst		**map;
	t_lst		*sub_map;

	if (shell->hash.map == NULL)
		return (FAILURE);
	map = shell->hash.map;
	shell->hash.value = get_hash(process->av[0], shell->hash.size);
	if (map[shell->hash.value] == NULL)
		return (FAILURE);
	sub_map = map[shell->hash.value];
	while (sub_map)
	{
		if (ft_strequ(process->av[0], ((t_db*)(sub_map->content))->key))
		{
			if (ft_access(((t_db*)(sub_map->content))->value, F_OK | X_OK) != SUCCESS)
				return (SUCCESS);
			process->bin = ft_strdup(((t_db*)(sub_map->content))->value);
			((t_db*)(sub_map->content))->hit += 1;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}
