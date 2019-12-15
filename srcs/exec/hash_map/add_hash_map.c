/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/15 15:53:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	fill_hash_map(t_core *shell, char *key, char *value, u_int8_t format)
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

int8_t	hash_map_dispatcher(t_core *shell, t_process *process, u_int8_t format)
{
	t_lst	*head_ref;
	t_db	*db;
	u_int32_t hash;
	size_t	i;

	i = 3;
	if (format & HASH_DEFAULT)
		return(fill_hash_map(shell, process->av[0], process->bin, format));
	while (process->av[i])
	{
		hash = get_hash(process->av[i], shell->hash.size);
		if (shell->hash.map[hash])
			db = shell->hash.map[hash]->content;
		head_ref = shell->hash.map[hash];
		while (shell->hash.map[hash])
		{
			if (ft_strequ(process->av[i], db->key) == TRUE)
			{
				ft_strdel(&(db->value));
				db->value = ft_strdup(process->av[2]);
				break ;
			}
			shell->hash.map[hash] = shell->hash.map[hash]->next;
		}
		if (shell->hash.map[hash] == NULL)
		{
			shell->hash.map[hash] = head_ref;
			if (fill_hash_map(shell, process->av[i], process->av[2], format) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	return(SUCCESS);
}
int8_t	add_hash_map(t_core *shell, t_process *process, u_int8_t format)
{
	if (format & HASH_DEFAULT && process->bin == NULL)
		return (FAILURE);
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (FAILURE);
	return(hash_map_dispatcher(shell, process, format));
}
