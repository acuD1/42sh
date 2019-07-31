/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:32:46 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/27 14:52:45 by arsciand         ###   ########.fr       */
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
	/*
	** NOT IMPLEMENTED YET
	if (shell->default_env == TRUE)
		set_default_env(shell, env);
	else
	{
		if (shell->env_mode == TRUE)
			env = shell->tmp_env;
		else
			env = shell->env;
	}*/
	env = shell->env;
	if (!(envp = ft_memalloc(sizeof(envp) * ((ft_lstlen(env)) + 1))))
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoinf(ft_strjoin(((t_db*)(env->content))->key, "="),
						((t_db*)(env->content))->value, 1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
