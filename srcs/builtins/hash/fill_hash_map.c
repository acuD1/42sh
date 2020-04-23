/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hash_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

int8_t			fill_exec
	(t_core *shell, const char *key, const char *value, enum e_hash fmt)
{
	float	load_factor;

	shell->hash.lenght++;
	load_factor = (float)shell->hash.lenght / shell->hash.size;
	if (load_factor > (float)MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);
	shell->hash.value = get_hash(key, shell->hash.size);
	if (!(ft_lstappend(&shell->hash.map[shell->hash.value],
		ft_lstnew(fetch_hash_db(&shell->db, key, value, fmt),
		sizeof(t_db)))))
		return (FAILURE);
	return (SUCCESS);
}

int8_t			fill_path
	(t_core *shell, t_process *process, enum e_hash fmt, size_t i)
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
			break ;
		}
		map = map->next;
	}
	if (map == NULL
		&& fill_exec(shell, process->av[i], process->av[2], fmt) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	is_hashed(t_core *shell, t_process *process, size_t i)
{
	t_lst	*sub_map;

	if (ft_strchr(process->av[i], '/'))
		return (SUCCESS);
	shell->hash.value = get_hash(process->av[i], shell->hash.size);
	sub_map = shell->hash.map[shell->hash.value];
	while (sub_map)
	{
		if (ft_strequ(process->av[i], ((t_db*)sub_map->content)->key))
		{
			((t_db*)sub_map->content)->hit = 0;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}

int8_t			fill_default
	(t_core *shell, t_process *process, enum e_hash fmt, size_t i)
{
	t_process	process_tmp;

	(void)fmt;
	if ((is_a_blt(process->av[i]) != FAILURE)
		|| (is_hashed(shell, process, i) == SUCCESS))
		return (SUCCESS);
	ft_bzero(&process_tmp, sizeof(t_process));
	process_tmp.blt = TRUE;
	if (!(process_tmp.av = malloc(sizeof(char *) * (2))))
		return (FAILURE);
	process_tmp.av[0] = ft_strdup(process->av[i]);
	process_tmp.av[1] = NULL;
	if (get_bin_path(shell, &process_tmp) != SUCCESS || process_tmp.bin == NULL)
		ft_dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n",
			process->av[i]);
	else
		fill_exec(shell, process_tmp.av[0], process_tmp.bin, H_DEF);
	ft_strdel(&process_tmp.bin);
	ft_tabdel(&process_tmp.av);
	is_hashed(shell, process, i);
	return (SUCCESS);
}
