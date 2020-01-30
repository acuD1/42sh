/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:14:29 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/14 16:14:33 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t add_assign_env(t_core *shell, char *key, char *value)
{
	if (!key || !shell->env)
		return (FAILURE);
	if (edit_var(shell, key, value, INTERNAL_VAR) != SUCCESS)
	{
		// free(value);
		return (FAILURE);
	}
	return (TRUE);
}

void		expansion_assign(t_core *shell, t_process *process)
{
	t_lst *lst;
	t_lst *tmp;
	char *res;

	if (!process->assign_list || !shell)
		return ;
	res = NULL;
	tmp = NULL;
	lst = process->assign_list;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_db*)lst->content)->value)))
			add_assign_env(shell, ((t_db*)lst->content)->key, res);
		else
			add_assign_env(shell, ((t_db*)lst->content)->key, NULL);
		tmp = lst;
		lst = lst->next;
		ft_strdel(&((t_db*)tmp->content)->key);
		ft_strdel(&((t_db*)tmp->content)->value);
	}
	process->envp = set_envp(shell);
	// ft_printtab(process->envp);
}
