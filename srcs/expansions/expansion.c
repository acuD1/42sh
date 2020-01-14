/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/16 04:59:06 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t is_expansion(e_pstate id)
{
	if (id == P_TILDEP)
		return (1);
	else if (id == P_TILDEM)
		return (2);
	else if (id == P_TILDE)
		return (3);
	else if ( id == P_DBPARENT)
		return (4);
	else if ( id == P_PARENT)
		return (5);
	else if ( id == P_BRACKET)
		return (6);
	else if ( id == P_HOOK)
		return (7);
	else if (id == P_DOLLAR)
		return (8);
	else if (id == P_DBQUOTE || id == P_WORD || id == P_BQUOTE)
		return (9);
	return (0);
}

char *no_exp(char *data, t_core *shell)
{
	(void)shell;
	return (data);
}

int8_t add_assign_env(t_lst *lst, t_core *shell)
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
		if (edit_var(shell, ((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = lst;
		lst = lst->next;
		free(((t_db*)tmp->content)->key);
		free(tmp);
	}
	return (TRUE);
}

int expelliarmus(char *src, int index, char **dst, t_core *shell)
{
	t_expansion toto;
	e_pstate state;
	char *exp;
	char *trans;

	exp = NULL;
	trans = NULL;
	state = P_EXP_INTERRUPT;
	init_expansionat(&toto);
	if (src[index] == '$')
	{
		state = find_expansion(&src[index]);
		toto.erience = is_expansion(state);
		if ((exp = get_expansion(&src[index], state)))
			if ((trans = toto.sionat[toto.erience](exp, shell)))
				*dst = ft_strjoinf(*dst, trans, 4);
		return ((index += ft_strlen(exp)));
	}
	return (index);
}

char *exp_dbquote(char *data, t_core *shell)
{
	int index;
	char *res;
	char *tmp;

	index = 0;
	tmp = ft_strsub(data, 0, 1);
	res = ft_strnew(0);
	while (data[index])
	{
		if (data[index] == '\'')
		{
			index++;
			while (data[index] && data[index] != '\'')
				index++;
		}
		index = expelliarmus(data, index, &res, shell);
		tmp = ft_strsub(data, index, 1);
		res = ft_strjoinf(res, tmp, 4);
		index++;
	}
	return (res);
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

void		expansion(t_core *shell, t_process *process)
{
	t_lst *lst;
	t_expansion exp;
	char *tmp;

	if (!process->tok_list || !shell)
		return ;
	tmp = NULL;
	lst = process->tok_list;
	init_expansionat(&exp);
	while (lst)
	{
		exp.erience = is_expansion(((t_token*)lst->content)->id);
		if ((tmp = exp.sionat[exp.erience](((t_token*)lst->content)->data, shell)))
		{
			process->av = ft_add_arg_cmd_process(process->av, tmp);
			free (tmp);
		}
		lst = lst->next;
	}
}
