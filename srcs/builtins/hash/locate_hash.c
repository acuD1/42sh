/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:20:26 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 18:38:16 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

static int8_t	del_located_hash(t_core *shell, t_lst *node, t_process *process)
{
	if (((t_db*)node->content)->value[0] == '.'
		&& ((t_db*)node->content)->value[1] == '/'
		&& ((t_db*)node->content)->value[2] != 0)
		((t_db*)node->content)->hit += 1;
	else
		hash_key_remover(shell, process->av[0]);
	process->bin = NULL;
	return (SUCCESS);
}

int8_t			locate_hash(t_core *shell, t_process *process)
{
	t_lst	*sub_map;

	shell->hash.value = get_hash(process->av[0], shell->hash.size);
	if (shell->hash.map == NULL || shell->hash.map[shell->hash.value] == NULL)
		return (FAILURE);
	sub_map = shell->hash.map[shell->hash.value];
	while (sub_map)
	{
		if (ft_strequ(process->av[0], ((t_db*)sub_map->content)->key))
		{
			if (ft_access(((t_db*)sub_map->content)->value,
				F_OK | X_OK) != SUCCESS)
				return (del_located_hash(shell, sub_map, process));
			process->bin = ft_strdup(((t_db*)sub_map->content)->value);
			((t_db*)sub_map->content)->hit += 1;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}
