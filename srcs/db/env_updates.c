/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:12:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/15 19:12:56 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Increment SHLVL : search SHLVL in the env list, increment the value
**	or create the t_db and assign the value to 1
*/

int8_t	increment_shlvl(t_lst **env)
{
	char	*shlvl;
	t_db	*db;

	shlvl = NULL;
	if (env == NULL || (db = get_or_create_db(env, "SHLVL", ENV_VAR)) == NULL)
	{
		return (FAILURE);
	}
	shlvl = ft_itoa(ft_atoi(db->value) + 1);
	ft_strdel(&(db->value));
	db->value = shlvl;
	return (SUCCESS);
}

/*
**	Update pwd : search PWD in the env list,
**	get the pointer to the db or create it if not existing
**	and then assign the current working dir path to value.
*/

int8_t	update_pwd(t_lst **env)
{
	char	buf[1025];
	t_db	*db;

	ft_bzero(buf, 1025);
	getcwd(buf, 1025);
	db = NULL;
	if (env == NULL || (db = get_or_create_db(*env, "PWD", ENV_VAR)) == NULL)
	{
		return (FAILURE);
	}
	ft_strdel(&(db->value));
	db->value = ft_strdup(buf);
	return (SUCCESS);
}
