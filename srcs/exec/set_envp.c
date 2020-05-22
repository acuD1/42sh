/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:32:46 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/01 23:49:24 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	This function format correctly all env variables for execve :KEY=VALUE
**	Why don't we use directly char **environ of the main ?
**	Because we need to implement differents env. Like if we set env -i
**	SOME=VALUE to a binary, and having a correct environnement.
*/

static void	check_env(t_lst *env, char **envp, size_t *i, int join_it)
{
	while (env != NULL)
	{
		if (((t_db*)env->content)->type == (EXPORT_VAR | INTERNAL_VAR))
		{
			if (join_it == TRUE)
			{
				envp[*i] = ft_strjoinf(
						ft_strjoin(((t_db*)(env->content))->key, "=")
						, ((t_db*)(env->content))->value, 1);
			}
			*i += 1;
		}
		env = env->next;
	}
}

char		**set_envp(t_core *shell)
{
	char	**envp;
	size_t	i;

	i = ft_lstlen(shell->env);
	if (!(envp = ft_memalloc(sizeof(envp) * (i + 1))))
		return (NULL);
	i = 0;
	check_env(shell->env, envp, &i, TRUE);
	envp[i] = NULL;
	return (envp);
}
