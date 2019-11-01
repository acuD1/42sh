/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:32:46 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/28 03:11:10 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	This function format correctly all env variables for execve :
**	KEY=VALUE
**	Why don't we use directly char **environ of the main ?
**	Because we need to implement differents env. Like if we set env -i SOME=VALUE
**	to a binary, and having a correct environnement.
*/

char	**set_envp(t_core *shell)
{
	t_lst	*env;
	char	**envp;
	size_t	i;

	i = 0;
	env = shell->env;
	while (env != NULL)
	{
		if (((t_db*)env->content)->type & ENV_VAR)
			i++;
		env = env->next;
	}
	if (!(envp = ft_memalloc(sizeof(envp) * (i + 1))))
		return (NULL);
	env = shell->env;
	i = 0;
	while (env)
	{
		if (((t_db*)env->content)->type & ENV_VAR)
		{
			envp[i] = ft_strjoinf(ft_strjoin(((t_db*)(env->content))->key, "=")
					, ((t_db*)(env->content))->value, 1);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
