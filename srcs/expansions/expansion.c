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
	else if (id == P_DBQUOTE || id == P_BQUOTE || id == P_ASSIGN)
		return (9);
	return (0);
}

char *no_exp(char *data, t_core *shell)
{
	(void)shell;
	return (data);
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
		index = ft_strlen(exp) + index;
		ft_strdel(&exp);
		return (index);
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
		if ((size_t)index == ft_strlen(data))
			break ;
		tmp = ft_strsub(data, index, 1);
		res = ft_strjoinf(res, tmp, 4);
		index++;
	}
	return (res);
}

void expansion(t_core *shell, t_process *process)
{
	if (!process || !shell)
		return ;
	
	if (process->assign_list)
	{
		expansion_assign(shell, process);
		add_assign_env(process->assign_list, shell);
	}
	if (process->tok_list)
		expansion_tok(shell, process);
	if (process->redir_list)
		expansion_redir(shell, process);
}
