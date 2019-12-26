/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/26 12:41:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	fill_dflt(t_core *shell, char *key, char *value, u_int8_t format)
{
	float	load_factor;

	shell->hash.lenght++;
	load_factor = (float)shell->hash.lenght / shell->hash.size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);
	shell->hash.value = get_hash(key, shell->hash.size);
	ft_lstappend(&shell->hash.map[shell->hash.value],
		ft_lstnew(fetch_hash_db(&shell->db, key,
						value, format), sizeof(t_db)));
	return (SUCCESS);
}

int8_t	fill_path(t_core *shell, t_process *process, u_int8_t format, size_t i)
{
	t_lst		*map;
	u_int32_t	hash;

	hash = get_hash(process->av[i], shell->hash.size);
	map = shell->hash.map[hash];
	while (map)
	{
		if (ft_strequ(process->av[i], ((t_db*)map->content)->key) == TRUE)
		{
			ft_strdel(&(((t_db*)map->content)->value));
			((t_db*)map->content)->value = ft_strdup(process->av[2]);
			((t_db*)map->content)->hit = 0;
			return (SUCCESS);
		}
		map = map->next;
	}
	if (map == NULL
		&& fill_dflt(shell, process->av[i], process->av[2], format) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	hash_map_dispatcher(t_core *shell, t_process *process, u_int8_t format)
{
	size_t	i;

	i = 3;
	if (format & HASH_DEFAULT && process->bin == NULL)
		return (FAILURE);
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (FAILURE);
	if (format & HASH_DEFAULT)
		return (fill_dflt(shell, process->av[0], process->bin, format));
	while (process->av[i] && fill_path(shell, process, format, i) == SUCCESS)
		i++;
	return (SUCCESS);
}
