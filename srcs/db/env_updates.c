/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:12:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/01 23:43:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

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

	db = NULL;
	if (shell && (db = get_or_create_db(
		shell, "SHLVL", EXPORT_VAR | INTERNAL_VAR)) != NULL)
	{
		if (ft_atol(db->value, &value) != SUCCESS)
			new_value = 0;
		else if (value < 0 || value > 999)
			new_value = -1;
		else
			new_value = ((value & 8000000000000000) >> 32) + value & 0xFFF;
		if (value > 999)
			ft_dprintf(STDERR_FILENO
			, "42sh: warning: shell level (%lli) too high, resetting to 1\n"
			, value);
		shlvl = (value == 999) ? ft_strnew(0) : ft_itoa(new_value + 1);
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
	int		tablen;

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
