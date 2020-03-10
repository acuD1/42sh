/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:40:15 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/10 18:58:37 by arsciand         ###   ########.fr       */
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

int8_t			cd_oldpwd(t_core *shell)
{
	t_db	*db_oldpwd;
	int8_t	errnum;

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
