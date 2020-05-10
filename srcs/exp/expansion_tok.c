/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:02:26 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/12 17:07:37 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*apply_exp_tok(t_core *shell, char *data, char *tmp, char ***t)
{
	char		*res;

	res = NULL;
	res = inhibiteurs_expansion(data, shell, 0);
	if (shell->subst_error)
	{
		ft_strdel(&tmp);
		ft_tabdel(&*t);
		ft_strdel(&res);
		shell->status = 1;
		return (NULL);
	}
	if (*res)
	{
		ft_strdel(&tmp);
		*t = ft_add_arg_cmd_process(*t, res);
		tmp = ft_strdup(res);
	}
	else if (!*res && (ft_strchr(data, '\'')
		|| ft_strchr(data, '\"')))
		*t = ft_add_arg_cmd_process(*t, res);
	ft_strdel(&res);
	return (tmp);
}

void			expansion_tok(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*tmp;

	tmp = NULL;
	lst = process->tok_list;
	shell->subst_error = 0;
	while (lst)
	{
		if (((t_token*)lst->content)->data)
			tmp = apply_exp_tok(shell, ((t_token*)lst->content)->data,
				tmp, &process->av);
		lst = lst->next;
	}
	update_underscore_value(tmp, shell, process);
}
