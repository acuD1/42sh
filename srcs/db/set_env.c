/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:02:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/25 02:23:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	increment_shlvl(shell);
	update_pwd(shell);
	update_(shell);
	update_ifs(shell);
	update_termsize(shell);
	create_term(shell);
	update_histfile(shell);
	update_hist_size(shell);
	update_histfile_size(shell);
	update_version(shell);

	if (shell->env == NULL)
		return (FAILURE);
	return (SUCCESS);
}
