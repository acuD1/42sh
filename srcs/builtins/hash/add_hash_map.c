/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:38:40 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 18:37:25 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	fill_exec
	(t_core *shell, char *key, char *value, enum e_hash fmt)
{
	float	load_factor;

	shell->hash.lenght++;
	load_factor = (float)shell->hash.lenght / shell->hash.size;
	if (load_factor > MAX_LOAD_F && resize_hash_map(shell) != SUCCESS)
		return (FAILURE);
	shell->hash.value = get_hash(key, shell->hash.size);
	if (!(ft_lstappend(&shell->hash.map[shell->hash.value],
		ft_lstnew(fetch_hash_db(&shell->db, key, value, fmt),
		sizeof(t_db)))))
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	fill_path
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

static int8_t	fill_default
	(t_core *shell, t_process *process, enum e_hash fmt, size_t i)
{
	t_process	process_tmp;

	(void)fmt;
	if (is_hashed(shell, process, i) == SUCCESS)
		return (SUCCESS);
	ft_bzero(&process_tmp, sizeof(t_process));
	if (!(process_tmp.av = malloc(sizeof(char *) * (2))))
		return (FAILURE);
	process_tmp.av[0] = ft_strdup(process->av[i]);
	process_tmp.av[1] = NULL;
	if (get_bin_path(shell, &process_tmp) != SUCCESS)
		dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", process->av[i]);
	ft_strdel(&process_tmp.bin);
	ft_tabdel(&process_tmp.av);
	is_hashed(shell, process, i);
	return (SUCCESS);
}

void			hash_map_dispatcher
	(t_core *shell, t_process *process, enum e_hash fmt)
{
	size_t			i;
	static int8_t	(*fill_fp[3])() = {fill_default, fill_exec, fill_path};

	if (fmt == H_EXEC && process->bin == NULL)
		return ;
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
		return (hash_error(&shell->hash));
	if (fmt == H_EXEC)
	{
		if (fill_fp[fmt](shell, process->av[0], process->bin, fmt) != SUCCESS)
			return (hash_error(&shell->hash));
	}
	else
	{
		i = fmt + 1;
		while (process->av[i])
		{
			if (fill_fp[fmt](shell, process, fmt, i) != SUCCESS)
				return (hash_error(&shell->hash));
			i++;
		}
	}
	if (shell->hash.lenght == 0)
		reset_hash(&shell->hash);
}
