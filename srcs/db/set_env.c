/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:02:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/28 02:14:04 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Setup all required variables for the shell
*/

int8_t	init_env(t_core *shell)
{
	static int8_t	(*inits[9])(t_core *shell) = {increment_shlvl, update_pwd
		, update_ifs, update_termsize, create_term, update_histfile
			, update_hist_size, update_histfile_size, update_version};
	int				i;

	i = 0;
	while (i < 9)
	{
		inits[i](shell);
		i++;
	}
	return (SUCCESS);
}

int8_t	set_env(t_core *shell, char **argv, char **environ)
{
	(void)argv;
	size_t	i;

	i = 0;

	while (*environ && environ[i])
	{
		ft_lstappend(&shell->env,
			ft_lstnew(fetch_db(&shell->db, environ[i], ENV_VAR), sizeof(t_db)));
		i++;
	}
	init_env(shell);
	if (shell->env == NULL)
		return (FAILURE);
	return (SUCCESS);
}
