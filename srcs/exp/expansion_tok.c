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

static int8_t	expansion_tok_handler
	(t_core *shell, t_process *process, char *res)
{
	if (shell->subst_error)
	{
		ft_tabdel(&process->av);
		ft_strdel(&res);
		shell->status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

static void		add_inhibiteur(t_process *process, char *res, char *tmp)
{
	process->av = ft_add_arg_cmd_process(process->av, res);
	ft_strdel(&tmp);
	tmp = ft_strdup(res);
}

void			expansion_tok(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		if (((t_token*)lst->content)->data)
		{
			res = inhibiteurs_expansion(((t_token*)lst->content)->data, shell);
			if (expansion_tok_handler(shell, process, res) != SUCCESS)
				return ;
			if (*res)
				add_inhibiteur(process, res, tmp);
			else if (!*res && (ft_strchr(((t_token*)lst->content)->data, '\'')
				|| ft_strchr(((t_token*)lst->content)->data, '\"')))
				process->av = ft_add_arg_cmd_process(process->av, res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
	update_underscore_value(tmp, shell, process);
}
