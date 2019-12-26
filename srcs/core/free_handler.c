/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:27:32 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/26 10:19:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	free_env(t_lst *env)
{
	t_lst	*tmp;

	while (env)
	{
		ft_strdel(&((t_db*)(env->content))->key);
		ft_strdel(&((t_db*)(env->content))->value);
		free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_prompt(t_core *shell)
{
	ft_strdel(&shell->term.buffer);
	ft_freejoblist(&shell->job_list);
}

void	free_hash_map(t_hash *hash)
{
	t_lst	*tmp;
	size_t	i;

	i = 0;
	if (!hash->map)
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
	free(hash->map);
	hash->map = NULL;
	hash->lenght = 0;
	hash->size = HASH_SIZE;
}

void			free_history(t_read *term)
{
	t_lst *tmp;

	while (term->history)
	{
		free(term->history->content);
		tmp = term->history;
		term->history = term->history->next;
		free(tmp);
		tmp = NULL;
	}
}
