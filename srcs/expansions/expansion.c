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

uint8_t is_expansion(e_estate id)
{
	if (id == E_TILDEP)
		return (1);
	else if (id == E_TILDEM)
		return (2);
	else if (id == E_TILDE)
		return (3);
	else if ( id == E_DBPARENT)
		return (4);
	else if ( id == E_PARENT)
		return (5);
	else if ( id == E_BRACKET)
		return (6);
	else if ( id == E_HOOK)
		return (7);
	else if (id == E_DOLLAR)
		return (8);
	else
		return (9);
	return (0);
}

char *no_exp(char *data, t_core *shell)
{
	(void)shell;
	(void)data;
	return (NULL);
}

int expelliarmus(char *src, int index, char **dst, t_core *shell)
{
	t_expansion toto;
	e_estate state;
	char *netero;
	char *trans;

	netero = NULL;
	trans = NULL;
	state = NB_EXPANSION_STATE;
	init_expansionat(&toto);
	if (src[index] == '$')
	{
		state = find_expansion(&src[index]);
		toto.erience = is_expansion(state);
		if ((netero = get_expansion(&src[index], state)))
			if ((trans = toto.sionat[toto.erience](netero, shell)))
				*dst = ft_strjoinf(*dst, trans, 4);
		index = ft_strlen(netero) + index;
		ft_strdel(&netero);
		return (index);
	}
	return (index);
}

char *exp_dbquote(char *data, t_core *shell)
{
	int index;
	int flag;
	char *res;
	char *tmp;

	index = 0;
	flag = 0;
	tmp = NULL;
	res = ft_strnew(0);
	while (data[index])
	{
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
	
	// if (process->assign_list)
	// {
	// 	expansion_assign(shell, process);
	// 	add_assign_env(process->assign_list, shell);
	// }
	if (process->tok_list)
		expansion_tok(shell, process);
	// if (process->redir_list)
		// expansion_redir(shell, process);
}
