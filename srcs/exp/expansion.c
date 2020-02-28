/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/13 20:52:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			expansion_tok(t_core *shell, t_process *process)
{
	t_lst			*lst;
	char			*res;

	if (!process->tok_list || !shell)
		return ;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		if (((t_token*)lst->content)->data)
		{
			res = inhibiteurs_expansion(((t_token*)lst->content)->data, shell);
			if (*res)
				process->av = ft_add_arg_cmd_process(process->av, res);
			else if (!*res && (ft_strchr(((t_token*)lst->content)->data, '\'')
				|| ft_strchr(((t_token*)lst->content)->data, '\"')))
				process->av = ft_add_arg_cmd_process(process->av, res);
			if (!lst->next)
				process->envp = add_underscore_envp(process->envp, res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
	ft_freetokenlist(&process->tok_list);
}

static void			expansion_assign(t_core *shell, t_process *process)
{
	t_lst			*lst;
	char			*res;

	if (!process->assign_list || !shell)
		return ;
	res = NULL;
	lst = process->assign_list;
	while (lst)
	{
		if (((t_db*)lst->content)->value)
		{
			res = inhibiteurs_expansion(((t_token*)lst->content)->data, shell);
			if (!process->av)
				add_assign_env(shell, ((t_db*)lst->content)->key,
					ft_strdup(res));
			else
				add_assign_envp(((t_db*)lst->content)->key,
					ft_strdup(res), &process->envp);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
}

static void			filename_heredoc_exp(t_core *shell, t_redir *redir)
{
	char			*res;

	res = NULL;
	if (!redir || !redir->op[1])
		return ;
	if (redir->type != 8 && redir->type != 7
		&& (res = inhibiteurs_expansion(redir->op[1], shell)))
	{
		if (!*res)
		{
			ft_dprintf(STDERR_FILENO, "42sh: %s :ambiguous redirect\n",
				redir->op[1]);
			shell->status = 1;
		}
		ft_strdel(&(redir->op[1]));
		redir->op[1] = ft_strdup(res);
		ft_strdel(&res);
	}
	if ((shell->is_interactive) && redir->heredoc
		&& (res = inhibiteurs_expansion(redir->heredoc, shell)))
	{
		ft_strdel(&(redir->heredoc));
		redir->heredoc = ft_strdup(res);
		ft_strdel(&res);
	}
}

static void			expansion_redir(t_core *shell, t_process *process)
{
	t_lst			*lst;

	if (!process->redir_list || !shell)
		return ;
	lst = process->redir_list;
	while (lst)
	{
		filename_heredoc_exp(shell, ((t_redir*)lst->content));
		lst = lst->next;
	}
}

void				expansion(t_core *shell, t_process *process)
{
	if (!process || !shell)
		return ;
	process->envp = set_envp(shell);
	if (process->tok_list)
		expansion_tok(shell, process);
	if (process->assign_list)
		expansion_assign(shell, process);
	if (process->redir_list)
		expansion_redir(shell, process);
	if (!process->av)
	{
		process->status = 0;
		shell->status = (!shell->status) ? 0 : 1;
		process->completed = TRUE;
	}
}
