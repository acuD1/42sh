/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:29:42 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:30:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char		*cd_pwd_error_handler
	(t_core *shell, const char *path, char *value)
{
	t_db *db_oldpwd;

	db_oldpwd = get_or_create_db(shell, "OLDPWD", EXPORT_VAR | INTERNAL_VAR);
	if (shell->cd.no_symbolic == TRUE)
		value = ft_strdup(".");
	else if (db_oldpwd->value && db_oldpwd->value[0] == '/')
		value = ft_strdup(path);
	else
	{
		if (ft_strequ(db_oldpwd->value, ".") == TRUE)
		{
			value = ft_strdup(path);
		}
		else
		{
			value = ft_strdup(db_oldpwd->value);
			value = ft_strjoinf(value, "/", 1);
			value = ft_strjoinf(value, shell->cd.dash == TRUE
										? shell->cd.tmp_pwd : (char *)path, 1);
			ft_strdel(&shell->cd.tmp_pwd);
		}
	}
	return (value);
}

static int8_t	cd_error_status(t_core *shell)
{
	static int error;

	if (shell->cd.pwd_error == TRUE && shell->cd.no_symbolic == FALSE)
	{
		error += 1;
		shell->cd.error = error;
		return (SUCCESS);
	}
	error = 0;
	return (SUCCESS);
}

int8_t			cd_update_pwd(t_core *shell, const char *pwd, const char *path)
{
	struct stat	db_stat;
	t_db		*db_pwd;
	char		buf[MAX_PATH + 1];
	char		*value;

	db_pwd = NULL;
	value = NULL;
	ft_bzero(buf, MAX_PATH + 1);
	if (shell != NULL
		&& (db_pwd = get_or_create_db(shell, "PWD", EXPORT_VAR
						| INTERNAL_VAR)) != NULL)
	{
		if (pwd)
			lstat(pwd, &db_stat);
		if (shell->cd.pwd_error >= TRUE)
			value = cd_pwd_error_handler(shell, path, value);
		else if (shell->cd.no_symbolic == TRUE || !(S_ISLNK(db_stat.st_mode)))
			value = ft_strdup(getcwd(buf, MAX_PATH));
		else
			value = ft_strdup(pwd);
		if (value && modify_db(db_pwd, value, 0) != NULL)
			return (cd_error_status(shell));
		ft_strdel(&value);
	}
	return (FAILURE);
}
