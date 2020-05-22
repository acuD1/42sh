/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:20:26 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:37:36 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>

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

static u_int8_t	check_moved_hash(char *ref, t_lst *node, t_core *shell)
{
	t_process	process_tmp;
	u_int8_t	ret;

	ret = 0;
	ft_bzero(&process_tmp, sizeof(t_process));
	if (!(process_tmp.av = malloc(sizeof(char *) * (2))))
	{
		hash_error(&shell->hash);
		return (FALSE);
	}
	process_tmp.av[0] = ft_strdup(ref);
	process_tmp.av[1] = NULL;
	get_bin_path(shell, &process_tmp);
	if (process_tmp.bin)
	{
		ret = 1;
		ft_strdel(&((t_db*)node->content)->value);
		((t_db*)node->content)->value = ft_strdup(process_tmp.bin);
		((t_db*)node->content)->hit = 1;
	}
	ft_strdel(&process_tmp.bin);
	ft_tabdel(&process_tmp.av);
	return (ret == 1 ? TRUE : FALSE);
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
			{
				if (check_moved_hash(process->av[0], sub_map, shell) == FALSE)
					return (del_located_hash(shell, sub_map, process));
			}
			process->bin = ft_strdup(((t_db*)sub_map->content)->value);
			((t_db*)sub_map->content)->hit += 1;
			return (SUCCESS);
		}
		sub_map = sub_map->next;
	}
	return (FAILURE);
}
