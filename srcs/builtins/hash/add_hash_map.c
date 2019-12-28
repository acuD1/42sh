/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/28 19:21:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	fill_exec(t_core *shell, char *key, char *value, u_int8_t format)
{
	float	load_factor;

	shell->hash.lenght++;
	load_factor = (float)shell->hash.lenght / shell->hash.size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);
	shell->hash.value = get_hash(key, shell->hash.size);
	if (!(ft_lstappend(&shell->hash.map[shell->hash.value],
		ft_lstnew(fetch_hash_db(&shell->db, key, value, format),
		sizeof(t_db)))))
		return (FAILURE);
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
			if (!(((t_db*)map->content)->value = ft_strdup(process->av[2])))
				return (FAILURE);
			((t_db*)map->content)->hit = 0;
			return (SUCCESS);
		}
		map = map->next;
	}
	if (map == NULL
		&& fill_exec(shell, process->av[i], process->av[2], format) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	fill_default(t_core *shell, t_process *process, size_t i)
{
	t_process process_tmp;

	ft_bzero(&process_tmp, sizeof(t_process));
	ft_strcpy(process_tmp.av[0], process->av[i]);
	if (get_bin_path(shell, &process_tmp) != SUCCESS)
	{
		ft_bzero(&process_tmp, sizeof(t_process));
		return (FAILURE);
	}
	ft_bzero(&process_tmp, sizeof(t_process));
	return (SUCCESS);
}


void	hash_map_dispatcher(t_core *shell, t_process *process, u_int8_t format)
{
	size_t i;

	if (format & HASH_EXEC && process->bin == NULL)
		return ;
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (hash_error(&shell->hash));
	if (format & HASH_EXEC && fill_exec(shell, process->av[0], process->bin, format) != SUCCESS)
		return (hash_error(&shell->hash));
	else
	{
		dprintf(STDERR_FILENO, "?\n");
		i = 2;
		if (format & HASH_PATH)
			i = 3;
		while (process->av[i])
		{
			if ((format & HASH_PATH && fill_path(shell, process, format, i) != SUCCESS)
				|| (format & HASH_DEFAULT && fill_default(shell, process, i) != SUCCESS))
				return (hash_error(&shell->hash));
			i++;
		}
	}
	dprintf(STDERR_FILENO, "la\n");
}
