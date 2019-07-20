/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:02:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/20 17:13:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	set_env(t_core *shell, char **environ)
{
	t_lst	*env;
	size_t	i;

	i = 0;
	env = NULL;

	/*
	NOT IMPLEMENTED YET
	if (environ == NULL || *environ == NULL)
		return (set_default_env(shell, env));*/

	while (environ[i])
	{
		ft_lstappend(&env,
			ft_lstnew(fetch_db(&shell->db, environ[i]), sizeof(t_db)));
		i++;
	}

	/*
	NOT IMPLEMENTED YET
	define_env_list(shell, env);*/

	if (env == NULL)
		return (FAILURE);
	return (SUCCESS);
}
