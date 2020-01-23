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
	else if ( id == E_PARENT || id == E_BQUOTE)
		return (5);
	else if ( id == E_BRACKET)
		return (6);
	else if ( id == E_HOOK)
		return (7);
	else if (id == E_DOLLAR)
		return (8);
	else if (id == E_DBQUOTE)
		return (9);
	else if (id == E_QUOTE)
		return (0);
	return (0);
}

char *no_exp(char *data, t_core *shell)
{
	(void)shell;
	(void)data;
	printf("COMMENT CA SE FESSE\n");
	return (NULL);
}

int expelliarmus(char *src, int index, char **dst, t_core *shell)
{
	t_expansion toto;
	e_estate state;
	char *hetero;
	char *trans;

	hetero = NULL;
	trans = NULL;
	state = NB_EXPANSION_STATE;
	init_expansionat(&toto);
	if (src[index] == '$' || src[index] == '~' || src[index] == '`')
	{
		state = find_expansion(&src[index]);
		toto.erience = is_expansion(state);
		if ((hetero = get_expansion(&src[index], state)))
			if ((trans = toto.sionat[toto.erience](hetero, shell)))
				*dst = ft_strjoinf(*dst, trans, 4);
		index = ft_strlen(hetero) + index;
		ft_strdel(&hetero);
		return (index);
	}
	return (index);
}

static void get_quotes_flags(char c, int *dbquote, int *quote)
{
	int guill;
	int apost;

	guill = *dbquote;
	apost = *quote;
	if (c == '\"')
	{
		if (!guill)
			guill = 1;
		else
			guill = 0;
	}
	if (c == '\'' && !guill)
	{
		if (!apost)
			apost = 1;
		else
			apost = 0;	
	}
	*dbquote = guill;
	*quote = apost;
}

char *exp_dbquote(char *data, t_core *shell)
{
	int index;
	int flag[2];
	char *res;
	char *tmp;

	index = 0;
	flag[0] = 0;
	flag[1] = 0;
	tmp = NULL;
	res = ft_strnew(0);
	while (data[index])
	{
		get_quotes_flags(data[index], &flag[0], &flag[1]);
		if (!flag[1])
		{
			index = expelliarmus(data, index, &res, shell);
			if ((size_t)index == ft_strlen(data))
				break ;
		}
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
