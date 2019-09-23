/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_tools.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:09:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/23 19:26:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	modify the db link with new datas
**	new_value takes a pointer to a string, NULL if you don't want to modify it.
**	new_type takes a 8 bits int (0 if you don't want to modify it)
*/

t_db	*modify_db(t_db	*db, char *new_value, u_int8_t new_type)
{
	if (db && new_value != NULL)
	{
		ft_strdel(&(db->value));
		db->value = new_value;
	}
	if (db && new_type != 0)
	{
		db->type = new_type;
	}
	if (!db)
		ft_strdel(&new_value);
	return (db);
}

/*
**	Search key corresponding in the env list and return a pointer
**	to the t_db or create it if not existing. (variant of search_db function)
*/

t_db	*get_or_create_db(t_core *core, char *key, u_int8_t var_type)
{
	t_db	*db;

	db = search_db(core->env, key);
	if (db == NULL)
	{
		ft_lstappend(&(core->env),
			ft_lstnew(fetch_db(&(core->db), key, var_type), sizeof(t_db)));
		db = search_db(core->env, key);
	}
	return (db);
}

/*
**	Search first key corresponding in the env list and return a pointer
**	to the t_db or NULL ifnot existing
*/

t_db	*search_db(t_lst *env, char *key)
{
	t_db	*db;

	db = NULL;
	while (env != NULL)
	{
		db = (t_db*)env->content;
		if (ft_strcmp(db->key, key) == 0)
			return (db);
		env = env->next;
	}
	return (NULL);
}
