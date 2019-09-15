/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_db.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:09:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/15 19:12:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Search key corresponding in the env list and return a pointer
**	to the t_db or create it if not existing. (variant of search_db function)
*/

t_db	*get_or_create_db(t_lst **env, char *key, u_int8_t var_type)
{
	t_db	*db;

	db = search_db(*env, key);
	if (db == NULL)
	{
		ft_lstappend(env,
			ft_lstnew(fetch_db(NULL, key, var_type), sizeof(t_db)));
		db = search_db(*env, key);
	}
	return (db);
}

/*
**	Search first key corresponding in the env list and return a pointer
**	to the t_db or NULL ifnot existing
*/

t_db	*search_db(t_lst *env, char *key)
{
	while (*env && env != NULL)
	{
		if (ft_strcmp(env->content->key, key) == 0)
			return ((t_db*)env->content);
		env = env->next;
	}
	return (NULL);
}
