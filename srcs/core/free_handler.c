/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:27:32 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/27 14:22:25 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	free_env(t_lst *env)
{
	t_lst	*tmp;

	while (env)
	{
		ft_strdel(&((t_db*)(env->content))->key);
		ft_strdel(&((t_db*)(env->content))->value);
		free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_prompt(t_core *shell, char *line)
{
	ft_strdel(&shell->bin);
	ft_tabdel(&shell->tokens);
	ft_strdel(&line);
}
