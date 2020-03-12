/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:21:41 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/05 00:24:05 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	modify the db link with new datas
**	new_value takes a pointer to a string, NULL if you don't want to modify it.
**	new_type takes a 8 bits int (0 if you don't want to modify it)
*/

t_db	*modify_db(t_db *db, char *new_value, u_int8_t new_type)
{
	if (db && new_value)
	{
		ft_strdel(&(db->value));
		db->value = new_value;
	}
	if (db && new_type != 0)
	{
		db->type |= new_type;
	}
	if (!db)
		ft_strdel(&new_value);
	return (db);
}

/*
**	Search key corresponding in the env list and return a pointer
**	to the t_db or create it if not existing. (variant of search_db function)
*/

t_db	*get_or_create_db(t_core *shell, const char *key, u_int8_t var_type)
{
	t_db	*db;

	db = search_db(shell->env, key);
	if (db == NULL)
	{
		ft_lstappend(&(shell->env),
			ft_lstnew(fetch_db(&(shell->db), key, var_type), sizeof(t_db)));
		db = search_db(shell->env, key);
	}
	return (db);
}

/*
**	Search first key corresponding in the env list and return a pointer
**	to the t_db or NULL ifnot existing
*/

t_db	*search_db(t_lst *env, const char *key)
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

/*
**	Delete the variable corresponding to the key
*/

int8_t	del_db(t_core *shell, const char *key)
{
	t_lst	*prev;
	t_lst	*env;

	prev = shell->env;
	env = shell->env;
	while (env != NULL && ft_strcmp(key, ((t_db*)env->content)->key) != 0)
	{
		prev = env;
		env = env->next;
	}
	if (env != NULL)
	{
		prev->next = env->next;
		if (prev == env)
			shell->env = env->next;
		ft_strdel(&(((t_db*)env->content)->key));
		ft_strdel(&(((t_db*)env->content)->value));
		ft_memdel(&env->content);
		ft_memdel((void**)&env);
		return (SUCCESS);
	}
	return (FAILURE);
}

int8_t	edit_var
	(t_core *shell, const char *name, char *value, u_int8_t var_type)
{
	t_db	*db;

	db = NULL;
	if (shell && (db = get_or_create_db(shell, name, var_type)) != NULL)
	{
		if (value && modify_db(db, value, var_type) != NULL)
			return (SUCCESS);
	}
	ft_strdel(&value);
	return (FAILURE);
}
