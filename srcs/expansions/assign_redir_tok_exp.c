/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redir_tok_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:03 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/04 20:47:06 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		add_assign_env(t_core *shell, char *key, char *value)
{
	if (!key || !shell->env)
		return (FAILURE);
	if (edit_var(shell, key, value, INTERNAL_VAR) != SUCCESS)
		return (FAILURE);
	return (TRUE);
}

void		add_assign_envp(char *key, char *value, char ***envp)
{
	char	*tmp;
	char	**tablo;

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
	t_lst	*lst;
	t_lst	*tmp;
	char	*res;

	if (!process->assign_list || !shell)
		return ;
	res = NULL;
	tmp = NULL;
	lst = process->assign_list;
	while (lst)
	{
		res = do_exp_et_quote(shell, ((t_db*)lst->content)->value);
		if (!process->av)
			add_assign_env(shell, ((t_db*)lst->content)->key, res);
		else
			add_assign_envp(((t_db*)lst->content)->key, res, &process->envp);
		tmp = lst;
		lst = lst->next;
		ft_strdel(&((t_db*)tmp->content)->key);
		ft_strdel(&((t_db*)tmp->content)->value);
	}
}

void		expansion_redir(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;

	if (!process->redir_list || !shell
			|| !((t_redir*)process->redir_list->content)->op[1])
		return ;
	lst = process->redir_list;
	res = NULL;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_redir*)lst->content)->op[1])))
		{
			ft_strdel(&(((t_redir*)lst->content)->op[1]));
			((t_redir*)lst->content)->op[1] = ft_strdup(res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
}

void		expansion_tok(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;

	if (!process->tok_list || !shell)
		return ;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		res = do_exp_et_quote(shell, ((t_token*)lst->content)->data);
		if (*res != '\0')
			process->av = ft_add_arg_cmd_process(process->av, res);
		ft_strdel(&res);
		lst = lst->next;
	}
	ft_freetokenlist(&process->tok_list);
}
