/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/28 18:41:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

static int8_t	cd_check_path(char *path)
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

static int8_t	change_dir(t_core *shell, char *path)
{
	char	buffer[MAX_PATH + 1];
	char	oldpwd[MAX_PATH + 1];

	ft_bzero(oldpwd, MAX_PATH + 1);
	ft_bzero(buffer, MAX_PATH + 1);
	getcwd(oldpwd, MAX_PATH);
	get_canonical_path(path, buffer);
	if (chdir(buffer) != SUCCESS)
	{
		ft_perror(path, "cd", cd_check_path(buffer));
		return (1);
	}
	update_oldpwd(shell, oldpwd);
	update_pwd(shell);
	return (SUCCESS);
}

static int8_t	cd_home(t_core *shell)
{
	t_db	*var;

	if ((var = search_db(shell->env, "HOME")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: HOME not set\n", 23);
		return (1);
	}
	dprintf(STDERR_FILENO, "%s\n", var->value);
	return (change_dir(shell, var->value));
}

static int8_t	cd_oldpwd(t_core *shell)
{
	t_db	*var;

	if ((var = search_db(shell->env, "OLDPWD")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: OLDPWD not set\n", 25);
		return (1);
	}
	if (cd_check_path(var->value) == SUCCESS)
		dprintf(STDERR_FILENO, "%s\n", var->value);
	return (change_dir(shell, var->value));
}

int8_t			builtin_cd(t_core *shell, t_process *process)
{
	int		argc;

	argc = ft_tablen(process->av);
	if (argc == 1 || ft_strcmp(process->av[1], "--") == 0)
		return (cd_home(shell));
	if (ft_strcmp(process->av[1], "-") == 0)
		return (cd_oldpwd(shell));
	return (change_dir(shell, process->av[1]));
	return (SUCCESS);
}
