/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:51:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 14:27:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

static int8_t	pwd_opt_parser(int ac, t_process *process, t_db *db, char *pwd)
{
	u_int64_t	options;

	options = ft_get_options(ac, process->av, "LP");
	if (options & (1ULL << 37))
		ft_dprintf(STDOUT_FILENO, "%s\n", db->value);
	else if (options & (1ULL << 41))
		ft_dprintf(STDOUT_FILENO, "%s\n", getcwd(pwd, MAX_PATH));
	else
		print_usage("pwd", options % 128, PWD_USAGE);
	return (SUCCESS);
}

static int8_t	pwd_check_path(const char *path)
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

int8_t			builtin_pwd(t_core *shell, t_process *process)
{
	struct stat	stat;
	t_db		*db;
	char		pwd[MAX_PATH + 1];
	int			ac;
	int			errnum;

	ft_bzero(pwd, MAX_PATH + 1);
	ac = ft_tablen(process->av);
	db = get_or_create_db(shell, "PWD", EXPORT_VAR | INTERNAL_VAR);
	lstat(db->value, &stat);
	if (S_ISLNK(stat.st_mode) == FALSE
		&& (errnum = pwd_check_path(db->value)) != SUCCESS)
	{
		shell->cd.pwd_error = TRUE;
		ft_dprintf(STDERR_FILENO, "|%d| %s %s", errnum, PWD_ERR, GETCWD_ERR);
		if (errnum == EACCES)
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		return (SUCCESS);
	}
	if (ac > 1)
		return (pwd_opt_parser(ac, process, db, pwd));
	ft_dprintf(STDOUT_FILENO, "%s\n", db->value);
	return (SUCCESS);
}
