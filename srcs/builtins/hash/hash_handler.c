/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:21:14 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:51:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <stdlib.h>

void	reset_hash(t_hash *hash)
{
	free(hash->map);
	hash->map = NULL;
	hash->lenght = 0;
	hash->size = HASH_SIZE;
}

void	free_hash_map(t_hash *hash)
{
	t_lst	*tmp;
	size_t	i;

	i = 0;
	if (!hash || !hash->map)
		return ;
	while (i < hash->size)
	{
		if (ft_lstlen(hash->map[i]) > 0)
		{
			tmp = NULL;
			while (hash->map[i])
			{
				ft_strdel(&((t_db*)(hash->map[i]->content))->key);
				ft_strdel(&((t_db*)(hash->map[i]->content))->value);
				free(hash->map[i]->content);
				tmp = hash->map[i];
				hash->map[i] = hash->map[i]->next;
				free(tmp);
			}
		}
		i++;
	}
	reset_hash(hash);
}

void	hash_error(t_hash *hash)
{
	ft_perror("hash", NULL, ENOMEM);
	free_hash_map(hash);
}

void	free_hash_key(t_hash *hash, t_lst *map)
{
	ft_strdel(&((t_db *)map->content)->key);
	ft_strdel(&((t_db *)map->content)->value);
	free(map->content);
	free(map);
	map = NULL;
	hash->lenght--;
	if (hash->lenght == 0)
		reset_hash(hash);
}
