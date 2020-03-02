/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/02 15:35:16 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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

static int8_t	cd_oldpwd(t_core *shell)
{
	t_db	*db_oldpwd;
	int		errnum;

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
	if (errnum != SUCCESS)
	{
		ft_perror(db_oldpwd->value, "cd", errnum);
		return (1);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", db_oldpwd->value);
	return (change_dir(shell, db_oldpwd->value));
}

static int8_t	cd_home(t_core *shell)
{
	char	pwd[MAX_PATH + 1];
	t_db	*var;

	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) == NULL && shell->cd.pwd_error == TRUE)
		ft_dprintf(STDERR_FILENO, "%s %s No such file or directory\n",
			CHDIR_ERR, GETCWD_ERR);
	if ((var = search_db(shell->env, "HOME")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: HOME not set\n", 23);
		return (1);
	}
	shell->cd.pwd_error = FALSE;
	if (chdir(var->value) != SUCCESS)
		ft_perror(var->value, "cd", cd_check_path(var->value));
	return (update_pwds(shell, pwd, NULL));
}

static int8_t	cd_opt_parser(t_core *shell, int ac, t_process *process)
{
	char		pwd[MAX_PATH + 1];
	u_int64_t	options;

	ft_bzero(pwd, MAX_PATH + 1);
	options = ft_get_options(ac, process->av, CD_OPT);
	if (!process->av[2])
		return (cd_home(shell));
	if (check_cd_arguments(process, ac) != SUCCESS)
		return (1);
	if (options & (1ULL << 37))
		return (change_dir(shell, process->av[2]));
	if (options & (1ULL << 41))
	{
		if (process->av[2] && process->av[2][0] == '-' && !process->av[2][1])
			return (cd_oldpwd(shell));
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
	shell->cd.no_symbolic = FALSE;
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
