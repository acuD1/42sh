/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:17:17 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/28 11:18:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_tokens(t_core *shell)
{
	char	**tokens;
	size_t	i;

	i = 0;
	tokens = shell->tokens;
	while (tokens[i])
	{
		dprintf(STDOUT_FILENO, "TOKEN[%zu] = |%s|\n", i, tokens[i]);
		i++;
	}
}

void	print_env(t_core *shell)
{
	t_lst	*env;

	env = shell->env;
	while (env)
	{
		dprintf(STDOUT_FILENO, "[KEY] = |%s|\n[VALUE] = |%s|\n",
			((t_db*)(env->content))->key, ((t_db*)(env->content))->value);
		env = env->next;
	}
}

/*
**	hash_table
*/

void	hash_module(t_core *shell)
{
	(void)shell;
	return ;
}

void	hash_table(t_core *shell)
{

}
