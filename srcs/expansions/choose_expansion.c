/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:14:39 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/14 16:14:44 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

// e_pstate ft_ffqtype(char *str)
// {
// 	if (!str || !(*str))
// 		return (P_END);
// 	while (*str)
// 	{
// 		if (*str == '\"')
// 			return (P_DBQUOTE);
// 		if (*str == '\'')
// 			return (P_QUOTE);
// 		if (*str == '`')
// 			return (P_BQUOTE);
// 		str++;
// 	}
// 	return (P_WORD);
// }

char *quote_mechanisms(char *str)
{
	char *new;
	int i;
	int j;
	e_pstate state;

	j = 0;
	i = 0;
	new = NULL;
	if (!str)
		return (NULL);
	new = ft_strnew(ft_strlen(str) + 1);
	state = P_END;
	i = 0;
	while (str[j])
	{
		if (str[j] == '\"' && (state == P_DBQUOTE || state == P_END))
		{
			if (state == P_DBQUOTE)
				state = P_END;
			else if (state == P_END)
				state = P_DBQUOTE;
			j++;
			if (str[j] == '\"')
				j++;
		}
		else if (str[j] == '\'' && (state == P_QUOTE || state == P_END))
		{
			if (state == P_QUOTE)
				state = P_END;
			else if (state == P_END)
				state = P_QUOTE;
			j++;
			if (str[j] == '\'')
				j++;
		}
		new[i] = str[j];
		i++;
		j++;

	}
	return (ft_strdup(new));
}

char *do_exp_et_quote(t_core *shell, char *data, e_pstate id)
{
	char *exp;
	char *unquoted;

	exp = NULL;
	unquoted = NULL;
	if ((exp = do_expansion(shell, data, id)))
	{
		if ((unquoted = quote_mechanisms(exp)))
		{
			ft_strdel(&exp);
			return (unquoted);
		}
	}
	return (NULL);
}

char *do_expansion(t_core *shell, char *data, e_pstate id)
{
	char *res;
	t_expansion exp;

	init_expansionat(&exp);
	res = NULL;
	exp.erience = is_expansion(id);
	if (!exp.erience)
		return (ft_strdup(data));
	if ((res = exp.sionat[exp.erience](data, shell)))
		return (res);
	return (NULL);
}

void init_expansionat(t_expansion 	*exp)
{
	exp->erience = 0;
	exp->sionat[0] = no_exp;
	exp->sionat[1] = exp_tilde;
	exp->sionat[2] = exp_tilde;
	exp->sionat[3] = exp_tilde;
	exp->sionat[4] = exp_math;
	exp->sionat[5] = exp_cmd_subs;
	exp->sionat[6] = exp_param;
	exp->sionat[7] = exp_math;
	exp->sionat[8] = exp_param;
	exp->sionat[9] = exp_dbquote;
}

void		expansion_redir(t_core *shell, t_process *process)
{
	t_lst *lst;
	char *res;
	e_pstate id;

	id = P_WORD;
	if (!process->redir_list || !shell
			|| !((t_redir*)process->redir_list->content)->op[1])
		return ;
	lst = process->redir_list;
	res = NULL;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_redir*)lst->content)->op[1], P_DBQUOTE)))
		{
			ft_strdel(&(((t_redir*)lst->content)->op[1]));
			((t_redir*)lst->content)->op[1] = ft_strdup(res);
			ft_strdel(&res);
		}
		else
		{
			printf("bash: %s: ambiguous redirect\n", ((t_redir*)lst->content)->op[1]);
			return ;
		}
		lst = lst->next;
	}
}

void		expansion_tok(t_core *shell, t_process *process)
{
	t_lst *lst;
	char *res;

	if (!process->tok_list || !shell)
		return ;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_token*)lst->content)->data, ((t_token*)lst->content)->id)))
		{
			process->av = ft_add_arg_cmd_process(process->av, res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
}
