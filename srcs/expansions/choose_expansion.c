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

static e_estate gla_quote(char *str, int *j, e_estate state)
{
	int i;

	i = *j;
	if (str[i] == '\"' && (state == E_DBQUOTE || state == NB_EXPANSION_STATE))
	{
		while (str[i] == '\"')
			i++;
		if (state == E_DBQUOTE)
			state = NB_EXPANSION_STATE;
		else if (state == NB_EXPANSION_STATE)
			state = E_DBQUOTE;
	}
	if (str[i] == '\'' && (state == E_QUOTE || state == NB_EXPANSION_STATE))
	{
		if (state == E_QUOTE)
			state = NB_EXPANSION_STATE;
		else if (state == NB_EXPANSION_STATE)
			state = E_QUOTE;
		while (str[i] == '\'')
			i++;
	}
	*j = i;
	return (state);
}

char *quote_mechanisms(char *str)
{
	char *new;
	int i;
	int j;
	e_estate state;

	j = 0;
	i = 0;
	new = NULL;
	if (!str)
		return (NULL);
	new = ft_strnew(ft_strlen(str));
	state = NB_EXPANSION_STATE;
	i = 0;
	while (str[j])
	{
		state = gla_quote(str, &j, state);
		if (!str[j])
			break ;
		new[i] = str[j];
		printf("%c    %d      %u\n", new[i], j, state);
		i++;
		j++;
	}
	return (new);
}

char *do_exp_et_quote(t_core *shell, char *data)
{
	char *exp;
	char *unquoted;

	exp = NULL;
	unquoted = NULL;
	if ((exp = do_expansion(shell, data)))
	{
		if ((unquoted = quote_mechanisms(exp)))
		{
			ft_strdel(&exp);
			return (unquoted);
		}
	}
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
	exp->sionat[9] = infinite_expansion;
}

char *do_expansion(t_core *shell, char *data)
{
	char *res;
	t_expansion exp;

	init_expansionat(&exp);
	res = NULL;
	exp.erience = is_expansion(E_DBQUOTE);
	if (!exp.erience)
		return (ft_strdup(data));
	if ((res = exp.sionat[exp.erience](data, shell)))
		return (res);
	return (NULL);
}

void		expansion_redir(t_core *shell, t_process *process)
{
	t_lst *lst;
	char *res;

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
	t_lst *lst;
	char *res;

	if (!process->tok_list || !shell)
		return ;
	res = NULL;
	lst = process->tok_list;
	while (lst)
	{
		if ((res = do_exp_et_quote(shell, ((t_token*)lst->content)->data)))
		{
			process->av = ft_add_arg_cmd_process(process->av, res);
			ft_strdel(&res);
		}
		lst = lst->next;
	}
	ft_freetokenlist(&process->tok_list);
}
