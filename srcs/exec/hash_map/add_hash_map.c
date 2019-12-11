/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/11 12:06:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	add_hash_map(t_core *shell, t_process *process, u_int8_t format)
{
	size_t	i;
	float	load_factor;

	i = 3;
	if (format & HASH_DEFAULT && process->bin == NULL)
		return(FAILURE);
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (FAILURE);
	load_factor = shell->hash.lenght / shell->hash.size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);
	if (format & HASH_DEFAULT)
	{
		shell->hash.value = get_hash(process->av[0], shell->hash.size);
		shell->hash.lenght++;
		ft_lstappend(&shell->hash.map[shell->hash.value],
			ft_lstnew(fetch_hash_db(&shell->db, process->av[0],
							process->bin), sizeof(t_db)));
	}
	while (format & HASH_PATH && process->av[i])
	{
		shell->hash.value = get_hash(process->av[i], shell->hash.size);
		if (shell->hash.map[shell->hash.value] && ft_strequ(process->av[i],
			((t_db*)shell->hash.map[shell->hash.value]->content)->key) == TRUE)
		{
			i++;
			continue;
		}
		ft_lstappend(&shell->hash.map[shell->hash.value],
			ft_lstnew(fetch_hash_db(&shell->db, process->av[i],
							process->av[2]), sizeof(t_db)));
		i++;
	}
	return (SUCCESS);
}
