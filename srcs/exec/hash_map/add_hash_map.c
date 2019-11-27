/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/27 11:55:33 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	add_hash_map(t_core *shell, t_hash *hash, t_process *process)
{
	float		load_factor;

	if (process->bin == NULL)
		return(FAILURE);
	/* If not hash.map, malloc */
	if (hash->map == NULL
		&& !(hash->map = ft_memalloc(sizeof(t_lst*) * hash->size)))
		return (FAILURE);
	dprintf(STDERR_FILENO, "MAP ALLOCED\n");
	/* Check factor, if > 0.75, increase hash size */
	load_factor = hash->lenght / hash->size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell, hash) != SUCCESS)
		return (FAILURE);

	/*	get hash value from the binary found in PATH */
	hash->value = get_hash(process->av[0], hash->size);

	hash->lenght++;
	/* add to hash map */
	ft_lstappend(&hash->map[hash->value],
		ft_lstnew(fetch_hash_db(&shell->db, process->av[0],
						process->bin), sizeof(t_db)));
	return (SUCCESS);
}
