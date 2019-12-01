/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/30 14:57:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	add_hash_map(t_core *shell, t_process *process)
{
	float	load_factor;

	if (process->bin == NULL)
		return(FAILURE);
	/* If not hash.map, malloc */
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (FAILURE);
	//dprintf(STDERR_FILENO, "MAP ALLOCED\n");
	/* Check factor, if > 0.75, increase hash size */
	load_factor = shell->hash.lenght / shell->hash.size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);

	/*	get hash value from the binary found in PATH */
	shell->hash.value = get_hash(process->av[0], shell->hash.size);

	shell->hash.lenght++;
	/* add to hash map */
	ft_lstappend(&shell->hash.map[shell->hash.value],
		ft_lstnew(fetch_hash_db(&shell->db, process->av[0],
						process->bin), sizeof(t_db)));

	return (SUCCESS);
}
