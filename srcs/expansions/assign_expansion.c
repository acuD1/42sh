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
		return (FAILURE);
	return (TRUE);
}

void add_assign_envp(char *key, char *value, char ***envp)
{
	char *tmp;
	char **tablo;

	tmp = NULL;
	tablo = *envp;
	tmp = ft_strjoin(key, "=");
	tmp = ft_strjoinf(tmp, value, 4);
	tablo = ft_add_arg_cmd_process(tablo, tmp);
	*envp = tablo;
	ft_strdel(&tmp);
}

void		expansion_assign(t_core *shell, t_process *process)
{
	t_lst *lst;
	t_lst *tmp;
	char *new_value;

	if (!process->assign_list || !shell)
		return ;
	new_value = NULL;
	tmp = NULL;
	lst = process->assign_list;
	while (lst)
	{
		new_value = do_exp_et_quote(shell, ((t_db*)lst->content)->value);
		if (!process->av)
			add_assign_env(shell, ((t_db*)lst->content)->key, new_value);
		else
			add_assign_envp(((t_db*)lst->content)->key, new_value, &process->envp);
		tmp = lst;
		lst = lst->next;
		ft_strdel(&((t_db*)tmp->content)->key);
		ft_strdel(&((t_db*)tmp->content)->value);
	}
}
