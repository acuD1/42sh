/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:12:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:55:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <unistd.h>

/*
**	Increment SHLVL : search SHLVL in the env list, increment the value
**	or if  not existing create the t_db and assign the value to 1
*/

int8_t	increment_shlvl(t_core *shell)
{
	int64_t	value;
	int32_t	new_value;
	char	*shlvl;
	t_db	*db;

	value = 0;
	if (shell && (db = get_or_create_db(
		shell, "SHLVL", EXPORT_VAR | INTERNAL_VAR)) != NULL)
	{
		if (db->value && ft_atol(db->value, &value) != SUCCESS)
			new_value = 0;
		if (value < 0 || value > 2147483647)
			new_value = 0;
		else
			new_value = (int32_t)value + 1;
		if (new_value > 999)
			ft_dprintf(STDERR_FILENO
			, "42sh: warning: shell level (%lli) too high, resetting to 1\n"
			, new_value);
		shlvl = ft_itoa((new_value >= 999) ? 1 : new_value);
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
	char	buf[MAX_PATH + 1];
	t_db	*db;
	char	*value;

	db = NULL;
	value = NULL;
	ft_bzero(buf, MAX_PATH + 1);
	if (shell != NULL && (db = get_or_create_db(
		shell, "PWD", EXPORT_VAR | INTERNAL_VAR)) != NULL)
	{
		getcwd(buf, MAX_PATH);
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
	size_t	tablen;

	db = NULL;
	value = NULL;
	if ((tablen = ft_tablen(argv)) <= 0)
		return (SUCCESS);
	if (shell != NULL && (db = get_or_create_db(
		shell, "_", INTERNAL_VAR)) != NULL)
	{
		value = ft_strdup(argv[tablen - 1]);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

int8_t	update_oldpwd(t_core *shell)
{
	t_db	*db_pwd;
	t_db	*db_oldpwd;
	char	*value;

	db_pwd = NULL;
	db_oldpwd = NULL;
	value = NULL;
	if (shell && (db_pwd = get_or_create_db(
					shell, "OLDPWD", EXPORT_VAR | INTERNAL_VAR)) != NULL
		&& (db_oldpwd = get_or_create_db(
				shell, "PWD", EXPORT_VAR | INTERNAL_VAR)) != NULL)
	{
		value = ft_strdup(db_oldpwd->value);
		if (value && modify_db(db_pwd, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
