/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:12:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/04 11:06:39 by mpivet-p         ###   ########.fr       */
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
		if (shlvl && modify_db(db, shlvl, 0))
			return (SUCCESS);
		ft_strdel(&shlvl);
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
	char	*value;

	db = NULL;
	value = NULL;
	ft_bzero(buf, 1025);
	if (shell != NULL && (db = get_or_create_db(shell, "PWD", ENV_VAR)) != NULL)
	{
		getcwd(buf, 1025);
		value = ft_strdup(buf);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update $_ : search $_ in the env list,
**	get the pointer to the db or create it if not existing
**	and then assign the last expanded argument.
*/

int8_t	update_last_arg(t_core *shell, char **argv)
{
	t_db	*db;
	char	*value;
	int		tablen;

	db = NULL;
	value = NULL;
	if ((tablen = ft_tablen(argv)) <= 0)
		return (FAILURE);
	if (shell != NULL && (db = get_or_create_db(shell, "_", ENV_VAR)) != NULL)
	{
		value = ft_strdup(argv[tablen - 1]);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
