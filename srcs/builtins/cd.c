/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/23 16:25:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int8_t	update_pwd_cd(t_core *shell, const char *pwd, const char *path)
{
	struct stat	db_stat;
	char	buf[MAX_PATH + 1];
	t_db	*db_pwd;
	t_db	*db_oldpwd;
	char	*value;
	static int	test;

	db_pwd = NULL;
	db_oldpwd = NULL;
	value = NULL;
	ft_bzero(buf, MAX_PATH + 1);
	//dprintf(STDERR_FILENO, "(1)\n");
	if (shell != NULL && (db_pwd = get_or_create_db(shell, "PWD", ENV_VAR)) != NULL)
	{
		if (pwd)
			lstat(pwd, &db_stat);
		if (shell->cd.pwd_error >= TRUE)
		{
			db_oldpwd = get_or_create_db(shell, "OLDPWD", ENV_VAR);
			//dprintf(STDERR_FILENO, "%d %s", shell->cd.no_symbolic, db_oldpwd->value);
			if (shell->cd.no_symbolic == TRUE)
			{
				value = ft_strdup(".");
			}
			else if (db_oldpwd->value && db_oldpwd->value[0] == '/')
				value = ft_strdup(path);
			else
			{
				if (ft_strequ(db_oldpwd->value, ".") == TRUE || ft_strequ(db_oldpwd->value, "..") == TRUE)
				{
					value = ft_strdup(path);
				}
				else
				{
					value = ft_strdup(db_oldpwd->value);
					value = ft_strjoinf(value, "/", 1);
					value = ft_strjoinf(value, shell->cd.dash == TRUE ? shell->cd.tmp_pwd : (char *)path, 1);
					ft_strdel(&shell->cd.tmp_pwd);
				}
			}
		}
		else if (shell->cd.no_symbolic == TRUE || S_ISLNK(db_stat.st_mode) == FALSE)
		{
			getcwd(buf, MAX_PATH);
			value = ft_strdup(buf);
		}
		else
			value = ft_strdup(pwd);
		if (value && modify_db(db_pwd, value, 0) != NULL)
		{
			if (shell->cd.pwd_error == TRUE && shell->cd.no_symbolic == FALSE)
			{
				test += 1;
				shell->cd.test = test;
				return (SUCCESS);
			}
			test = 0;
			return (SUCCESS);
		}
		ft_strdel(&value);
	}
	return (FAILURE);
}

static int8_t	cd_check_path(const char *path)
{
	int		errnum;

	errnum = 0;
	if (access(path, F_OK) == 0)
		errnum = is_a_dir(path);
	errnum = (errnum == EISDIR) ? 0 : errnum;
	if (errnum == 0)
		errnum = ft_access(path, X_OK);
	return (errnum);
}


static int8_t	change_dir(t_core *shell, const char *path)
{
	char		buffer[MAX_PATH + 1];
	char		tmp[MAX_PATH + 1];
	static char pwd[MAX_PATH + 1];
	t_db		*db;

	ft_bzero(buffer, MAX_PATH + 1);
	ft_bzero(tmp, MAX_PATH + 1);

	/* GOOD*/
	ft_bzero(tmp, MAX_PATH + 1);
	if (shell->cd.pwd_error == TRUE && ft_strlen(pwd) < 1)
	{
		ft_bzero(pwd, MAX_PATH + 1);
		db = get_or_create_db(shell, shell->cd.no_symbolic == TRUE ? "PWD" : "OLDPWD", ENV_VAR);
		ft_strcpy(pwd, db->value);
		dprintf(STDERR_FILENO, "%s %s No such file or directory\n", CHDIR_ERR, GETCWD_ERR);
		get_canonical_path(shell, path, buffer, pwd);
	//	dprintf(STDERR_FILENO, "pwd = |%s|\n", pwd);
		update_oldpwd(shell);
		update_pwd_cd(shell, buffer, path);
		return (SUCCESS);
	}
	get_canonical_path(shell, path, buffer, pwd);
	if (chdir(buffer) != SUCCESS)
	{
		if (shell->cd.pwd_error == TRUE)
		{
			if (shell->cd.no_symbolic == TRUE)
			{
				update_oldpwd(shell);
				update_pwd_cd(shell, buffer, path);
				return (1);
			}
			if (shell->cd.test > 0)
			{
				ft_perror(path, "cd", cd_check_path(buffer));
				shell->cd.test = shell->cd.test - 1;
				return (1);
			}
		}
		else
			ft_perror(path, "cd", cd_check_path(buffer));
	}
	update_oldpwd(shell);
	update_pwd_cd(shell, buffer, path);
	return (SUCCESS);
}


static int8_t	cd_oldpwd(t_core *shell)
{
	t_db	*db_pwd;
	t_db	*db_oldpwd;
	int		errnum;
	char	*tmp;
	char	pwd[MAX_PATH + 1];

	tmp = NULL;
	if ((db_oldpwd = search_db(shell->env, "OLDPWD")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: OLDPWD not set\n", 25);
		return (1);
	}
//	errnum = cd_check_path(db_oldpwd->value);
	if ((errnum = cd_check_path(db_oldpwd->value)) == SUCCESS && shell->cd.pwd_error >= TRUE)
	{
//		dprintf(STDERR_FILENO, "(1) test %d %s\n", shell->cd.test);
		if (shell->cd.test > 0 && getcwd(pwd, MAX_PATH) == NULL)
		{
			change_dir(shell, db_oldpwd->value);
			return (SUCCESS);
		}
		db_pwd = search_db(shell->env, "PWD");
		//shell->pwd_error = FALSE;
		tmp = ft_strdup(db_oldpwd->value);
		tmp = ft_strjoinf(tmp, "/", 1);
		tmp = ft_strjoinf(tmp, db_pwd->value, 1);
		dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
		shell->cd.tmp_pwd = ft_strdup(db_oldpwd->value);
		shell->cd.dash = TRUE;
		change_dir(shell, tmp);
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	if (errnum != SUCCESS)
	{
		ft_perror(db_oldpwd->value, "cd", errnum);
		return (1);
	}
	dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
	return (change_dir(shell, db_oldpwd->value));
}

static int8_t	cd_home(t_core *shell)
{
	char	pwd[MAX_PATH + 1];
	t_db	*var;

	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) == NULL && shell->cd.pwd_error == TRUE)
		dprintf(STDERR_FILENO, "%s %s No such file or directory\n", CHDIR_ERR, GETCWD_ERR);
	if ((var = search_db(shell->env, "HOME")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: HOME not set\n", 23);
		return (1);
	}
	shell->cd.pwd_error = FALSE;
	return (change_dir(shell, var->value));
}

static int8_t	cd_opt_parser(t_core *shell, int ac, t_process *process)
{
	char		pwd[MAX_PATH + 1];
	u_int64_t	options;

	ft_bzero(pwd, MAX_PATH + 1);
	options = ft_get_options(ac, process->av, CD_OPT);
	if (!process->av[2])
		return (cd_home(shell));
	if (options & (1ULL << 37))
		return (change_dir(shell, process->av[2]));
	if (options & (1ULL << 41))
	{
		if (getcwd(pwd, MAX_PATH) == NULL)
			shell->cd.pwd_error = TRUE;
		shell->cd.no_symbolic = TRUE;
		return (change_dir(shell, process->av[2]));
	}
	print_usage("cd", options % 128, CD_USAGE);
	return (SUCCESS);
}

int8_t			builtin_cd(t_core *shell, t_process *process)
{
	int		argc;
	char	tmp[MAX_PATH + 1];

	ft_bzero(tmp, MAX_PATH + 1);
	//if (shell->cd.pwd_error == FALSE)
	shell->cd.no_symbolic = FALSE;
	//if (getcwd(tmp, MAX_PATH) != NULL)
		//shell->cd.pwd_error = FALSE;
	argc = ft_tablen(process->av);
	if (argc == 1 || ft_strcmp(process->av[1], "--") == 0)
		return (cd_home(shell));
	if (ft_strcmp(process->av[1], "-") == 0 && !process->av[1][1])
		return (cd_oldpwd(shell));
	if (argc > 2)
		return (cd_opt_parser(shell, argc, process));
	change_dir(shell, process->av[1]);
	return (SUCCESS);
}
