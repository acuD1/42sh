/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:27:32 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 18:57:05 by arsciand         ###   ########.fr       */
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

void	free_prompt(t_core *shell)
{
	ft_strdel(&shell->term.buffer);
	ft_freejoblist(&shell->job_list);
}

void	free_history(t_read *term)
{
	t_lst	*tmp;

	while (term->history)
	{
		free(term->history->content);
		tmp = term->history;
		term->history = term->history->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_shell(t_core *shell)
{
	free_env(shell->env);
	free_prompt(shell);
	free_history(&shell->term);
	free_hash_map(&shell->hash);
}
