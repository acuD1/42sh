/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:02:36 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/17 19:11:09 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Setup all required variables for the shell
*/

static int8_t	init_env(t_core *shell)
{
	static int8_t	(*inits[16])(t_core *shell) = {increment_shlvl, update_pwd
		, update_ifs, update_termsize, create_term, update_histfile
		, update_hist_size, update_histfile_size, update_version
		, update_sharp_var, update_process_id, update_shell_name
		, update_shell_flags, update_exit_status, update_ps1, update_ps2};
	int				i;

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
		if (ft_strncmp("OLDPWD", environ[i], 6) != 0)
		{
			ft_lstappend(&shell->env,
				ft_lstnew(
					fetch_db(&shell->db, environ[i]
					, EXPORT_VAR | INTERNAL_VAR), sizeof(t_db)));
		}
		i++;
	}
	if (update_last_arg(shell, argv) != SUCCESS)
		return (FAILURE);
	if (init_env(shell) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
