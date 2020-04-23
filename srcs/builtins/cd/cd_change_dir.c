/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:41:27 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:50:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>

static int8_t	change_dir_perm_error
	(t_core *shell, const char *path, int8_t errnum)
{
	if (shell->cd.pwd_error == TRUE)
		ft_dprintf(STDERR_FILENO, "%s %s Permission denied\n",
			CHDIR_ERR, GETCWD_ERR);
	else
		errnum = ENOTDIR;
	ft_perror(path, "cd", errnum);
	return (1);
}

int8_t			update_pwds(t_core *shell, const char *buffer, const char *path)
{
	update_oldpwd(shell);
	cd_update_pwd(shell, buffer, path);
	return (SUCCESS);
}

static int8_t	change_dir_handler
	(t_core *shell, const char *path, int8_t errnum)
{
	if (shell->cd.pwd_error == TRUE)
	{
		if (shell->cd.no_symbolic == TRUE && errnum != EACCES)
			return (1);
		if (shell->cd.error > 0)
		{
			shell->cd.error = shell->cd.error - 1;
			ft_perror(path, "cd", errnum);
			return (1);
		}
	}
	ft_perror(path, "cd", errnum);
	return (1);
}

static void		cd_init_cache(t_core *shell, char *buffer, char *pwd, t_db *db)
{
	ft_bzero(buffer, MAX_PATH + 1);
	ft_bzero(pwd, MAX_PATH + 1);
	db = get_or_create_db(shell,
			shell->cd.no_symbolic == TRUE ? "PWD" : "OLDPWD",
			EXPORT_VAR | INTERNAL_VAR);
	ft_strcpy(pwd, db->value);
}

int8_t			change_dir(t_core *shell, const char *path)
{
	char		buffer[MAX_PATH + 1];
	static char pwd[MAX_PATH + 1];
	t_db		*db;
	int8_t		errnum;

	if (cd_use_cd_path(shell, path) == SUCCESS)
		return (SUCCESS);
	ft_bzero(buffer, MAX_PATH + 1);
	get_canonical_path(shell, path, buffer, pwd);
	db = get_or_create_db(shell, "PWD", EXPORT_VAR | INTERNAL_VAR);
	errnum = cd_check_path(buffer[0] == '\0' ? db->value : buffer);
	if (cd_check_path(db->value) == EACCES)
		return (change_dir_perm_error(shell, path, errnum));
	else if (shell->cd.pwd_error == TRUE
			&& ft_strlen(pwd) < 1 && cd_check_path(db->value) != EACCES)
	{
		cd_init_cache(shell, buffer, pwd, db);
		get_canonical_path(shell, path, buffer, pwd);
		ft_dprintf(STDERR_FILENO, "%s %s No such file or directory\n",
			CHDIR_ERR, GETCWD_ERR);
		return (update_pwds(shell, buffer, path));
	}
	if (chdir(buffer) != SUCCESS)
		return (change_dir_handler(shell, path, errnum));
	return (update_pwds(shell, buffer, path));
}
