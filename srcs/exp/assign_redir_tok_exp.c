/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redir_tok_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:03 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/13 18:17:00 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			add_assign_env(t_core *shell, const char *key, char *value)
{
	if (!key || !shell->env)
		return (FAILURE);
	if (edit_var(shell, key, value, INTERNAL_VAR) != SUCCESS)
		return (FAILURE);
	return (TRUE);
}

static void		add_assign_envp(const char *key, char *value, char ***envp)
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

void			expansion_assign(t_core *shell, t_process *process)
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
		res = do_expansion(shell, ((t_db*)lst->content)->value);
		if (!process->av)
			add_assign_env(shell, ((t_db*)lst->content)->key, ft_strdup(res));
		else
			add_assign_envp(((t_db*)lst->content)->key, ft_strdup(res), &process->envp);
		ft_strdel(&res);
		tmp = lst;
		lst = lst->next;
	}
}

void			expansion_redir(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;

	if (!process->redir_list || !shell)
		return ;
	lst = process->redir_list;
	res = NULL;
	while (lst)
	{
		if ((res = do_expansion(shell, ((t_redir*)lst->content)->op[1])))
		{
			if (!*res)
				ft_dprintf(STDERR_FILENO, "42sh: %s :ambiguous redirect\n", ((t_redir*)lst->content)->op[1]);
			ft_strdel(&(((t_redir*)lst->content)->op[1]));
			((t_redir*)lst->content)->op[1] = ft_strdup(res);
			ft_strdel(&res);
		}
		if ((res = do_expansion(shell, ((t_redir*)lst->content)->heredoc)))
		{
			ft_strdel(&(((t_redir*)lst->content)->heredoc));
			((t_redir*)lst->content)->heredoc = ft_strdup(res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
}

void			expansion_tok(t_core *shell, t_process *process)
{
	t_lst	*lst;
	char	*res;

	if (!process->tok_list || !shell)
		return ;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		res = do_expansion(shell, ((t_token*)lst->content)->data);
		if (*res != '\0')
			process->av = ft_add_arg_cmd_process(process->av, res);
		ft_strdel(&res);
		lst = lst->next;
	}
	ft_freetokenlist(&process->tok_list);
}
