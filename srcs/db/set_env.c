/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:02:36 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 17:16:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Setup all required variables for the shell
*/

static int8_t	init_env(t_core *shell)
{
	static int8_t	(*inits[16])(t_core *) = {increment_shlvl, update_pwd
		, update_ifs, update_termsize, create_term, update_histfile
		, update_hist_size, update_histfile_size, update_version
		, update_sharp_var, update_process_id, update_shell_name
		, update_shell_flags, update_exit_status, update_ps1, update_ps2};
	size_t			i;

	i = 0;
	while (i < 16)
	{
		if (inits[i](shell) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
**	Init the env at shell's lauch :
**	- Create required variables (internals and env)
**	- Modify Inherited vars from the parent shell
*/

int8_t			set_env(t_core *shell, char **argv, char **environ)
{
	size_t	i;

	i = 0;
	while (*environ && environ[i])
	{
		ft_lstappend(&shell->env, ft_lstnew(fetch_db(&shell->db
				, environ[i], EXPORT_VAR | INTERNAL_VAR), sizeof(t_db)));
		i++;
	}
	if (search_db(shell->env, "OLDPWD") == NULL)
	{
		fetch_db(&shell->db, "OLDPWD", EXPORT_VAR);
		ft_strdel(&(shell->db.value));
		ft_lstappend(&shell->env, ft_lstnew(&(shell->db), sizeof(t_db)));
	}
	if (update_last_arg(shell, argv) != SUCCESS)
		return (FAILURE);
	if (init_env(shell) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
