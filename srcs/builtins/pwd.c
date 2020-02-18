/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:51:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/18 16:39:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

static int8_t	pwd_opt_parser(int ac, t_process *process, t_db *db, char *pwd)
{
	u_int64_t	options;

	options = ft_get_options(ac, process->av, "LP");
	if (options & (1ULL << 37))
		dprintf(STDOUT_FILENO, "%s\n", db->value);
	else if (options & (1ULL << 41))
		dprintf(STDOUT_FILENO, "%s\n", getcwd(pwd, MAX_PATH));
	else
		print_usage("pwd", options % 128, PWD_USAGE);
	return (SUCCESS);
}

int8_t	builtin_pwd(t_core *shell, t_process *process)
{
	t_db	*db;
	char	pwd[MAX_PATH + 1];
	int		ac;

	ft_bzero(pwd, MAX_PATH + 1);
	if (getcwd(pwd, MAX_PATH) == NULL)
	{
		shell->pwd_error = TRUE;
		dprintf(STDERR_FILENO, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return (SUCCESS);
	}
	ac = ft_tablen(process->av);
	db = get_or_create_db(shell, "PWD", ENV_VAR);
	if (ac > 1)
		return (pwd_opt_parser(ac, process, db, pwd));
	dprintf(STDOUT_FILENO, "%s\n", db->value);
	return (SUCCESS);
}
