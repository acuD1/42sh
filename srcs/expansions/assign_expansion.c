/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:14:29 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/28 19:14:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	add_assign_env(t_lst *lst, t_core *shell)
{
	char	*value;
	t_lst	*tmp;

	if (!lst || !shell->env)
		return (FAILURE);
	value = NULL;
	tmp = NULL;
	while (lst)
	{
		value = ft_strdup(((t_db*)lst->content)->value);
		if (edit_var(shell,
				((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = lst;
		lst = lst->next;
		ft_strdel(&((t_db*)tmp->content)->key);
		ft_strdel(&((t_db*)tmp->content)->value);
		free(tmp);
	}
	return (TRUE);
}

void	expansion_assign(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;

	if (!process->assign_list || !shell)
		return ;
	res = NULL;
	lst = process->assign_list;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_db*)lst->content)->value)))
		{
			ft_strdel(&((t_db*)lst->content)->value);
			((t_db*)lst->content)->value = ft_strdup(res);
			ft_strdel(&res);
		}
		else
			ft_strdel(&((t_db*)lst->content)->value);
		lst = lst->next;
	}
}
