/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:12:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 02:54:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Increment SHLVL : search SHLVL in the env list, increment the value
**	or if  not existing create the t_db and assign the value to 1
*/

int8_t	increment_shlvl(t_core *shell)
{
	char	*shlvl;
	t_db	*db;

	shlvl = NULL;
	db = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "SHLVL", ENV_VAR)) != NULL)
	{
		shlvl = ft_itoa(ft_atoi(db->value) + 1);
		if (modify_db(db, shlvl, 0))
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
**	Update pwd : search PWD in the env list,
**	get the pointer to the db or create it if not existing
**	and then assign the current working dir path to value.
*/

int8_t	update_pwd(t_core *shell)
{
	char	buf[1025];
	t_db	*db;

	ft_bzero(buf, 1025);
	db = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "PWD", ENV_VAR)) != NULL)
	{
		getcwd(buf, 1025);
		if (modify_db(db, ft_strdup(buf), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}
