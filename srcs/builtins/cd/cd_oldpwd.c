/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:40:15 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/20 17:26:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <unistd.h>

static int8_t	cd_oldpwd_error(t_core *shell, t_db *db_oldpwd)
{
	t_db	*db_pwd;
	char	*tmp;

	db_pwd = search_db(shell->env, "PWD");
	tmp = ft_strdup(db_oldpwd->value);
	tmp = ft_strjoinf(tmp, "/", 1);
	tmp = ft_strjoinf(tmp, db_pwd->value, 1);
	ft_dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
	shell->cd.tmp_pwd = ft_strdup(db_oldpwd->value);
	shell->cd.dash = TRUE;
	change_dir(shell, tmp);
	ft_strdel(&tmp);
	return (SUCCESS);
}

static void		modifying_oldpwd(char *pwd, char *oldpwd)
{
	size_t	i;
	size_t	j;
	char	tmp[MAX_PATH + 1];

	ft_bzero(tmp, MAX_PATH);
	ft_strcpy(tmp, pwd);
	ft_bzero(pwd, MAX_PATH);
	i = ft_strlen(oldpwd);
	while (oldpwd[i] != '/')
		i--;
	j = 0;
	while (j < i)
	{
		pwd[j] = oldpwd[j];
		j++;
	}
	pwd[j++] = '/';
	i = 0;
	while (tmp[i])
	{
		pwd[j] = tmp[i];
		j++;
		i++;
	}
}

static int8_t	rewrite_oldpwd(t_core *shell, t_db *db_oldpwd, char *pwd)
{
	ft_bzero(pwd, MAX_PATH);
	readlink(db_oldpwd->value, pwd, MAX_PATH);
	modifying_oldpwd(pwd, db_oldpwd->value);
	ft_dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
	ft_strdel(&db_oldpwd->value);
	db_oldpwd->value = ft_strdup(pwd);
	return (change_dir(shell, db_oldpwd->value));
}

int8_t			cd_oldpwd(t_core *shell)
{
	struct stat	stat;
	t_db		*db_oldpwd;
	int8_t		errnum;
	char		pwd[MAX_PATH + 1];

	if ((db_oldpwd = search_db(shell->env, "OLDPWD")) == NULL
		|| db_oldpwd->value == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: OLDPWD not set\n", 25);
		return (1);
	}
	db_oldpwd->type = INTERNAL_VAR | EXPORT_VAR;
	if ((errnum = cd_check_path(db_oldpwd->value)) == SUCCESS
		&& shell->cd.pwd_error >= TRUE)
		return (cd_oldpwd_error(shell, db_oldpwd));
	lstat(db_oldpwd->value, &stat);
	if (errnum != SUCCESS && S_ISLNK(stat.st_mode) == FALSE)
	{
		ft_perror(db_oldpwd->value, "cd", errnum);
		return (1);
	}
	if (shell->cd.no_symbolic == TRUE && S_ISLNK(stat.st_mode) == TRUE)
		return (rewrite_oldpwd(shell, db_oldpwd, pwd));
	ft_dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
	return (change_dir(shell, db_oldpwd->value));
}
