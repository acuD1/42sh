/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:17:17 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/14 14:03:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_env(t_core *shell)
{
	t_lst	*env;

	env = shell->env;
	while (env)
	{
		dprintf(STDOUT_FILENO, "[KEY] = %-50s [VALUE] = %-40s [TYPE] = %i\n",
			((t_db*)(env->content))->key, ((t_db*)(env->content))->value, ((t_db*)(env->content))->type);
		env = env->next;
	}
}

/*
**	hash_table [VALGRIND BUG]
*/

void	print_hash_map_dev(t_hash *hash)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;
	int		z;

	i = 0;
	if (hash->map == NULL)
		return;
	map = hash->map;
	dprintf(STDERR_FILENO, "HASH SIZE = |%d| LENGHT = |%d|\n", hash->size, hash->lenght);
	cur_map = NULL;
	while (i < hash->size)
	{
		z = 0;
		cur_map = map[i];
		while (cur_map)
		{
			if (z > 0)
				dprintf(STDERR_FILENO, "\t");
			dprintf(STDERR_FILENO, "[%zu][%d] BIN|%s| PATH|%s|\n", i, z,
				((t_db*)(cur_map->content))->key,
				((t_db*)(cur_map->content))->value);
			cur_map = cur_map->next;
			z++;
		}
		i++;
	}
}

void	debug_analyzer(t_core *shell)
{
	t_lst *tmp;

	tmp = NULL;
	if (shell->job_list)
		tmp = shell->job_list;
	printf("LST LEN = |%zu|\n", ft_lstlen(tmp));
	tmp = NULL;
}
