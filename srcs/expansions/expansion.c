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

int expelliarmus(char *src, int *index, char **dst, t_core *shell)
{
	t_expansion toto;
	e_estate state;
	char *hetero;
	char *trans;
	int i;

	hetero = NULL;
	trans = NULL;
	state = NB_EXPANSION_STATE;
	init_expansionat(&toto);
	i = *index;
	state = find_expansion(&src[i]);
	toto.erience = is_expansion(state);
	if ((hetero = get_expansion(&src[i], state)))
	{
		if ((trans = toto.sionat[toto.erience](hetero, shell)))
			*dst = ft_strjoinf(*dst, trans, 4);
		*index += ft_strlen(hetero);
		return (0);
		ft_strdel(&hetero);
	}
	return (1);
}

static int get_quotes_flags(char *str, int *index, int *dbquote, int *quote)
{
	int guill;
	int apost;

	guill = *dbquote;
	apost = *quote;
	if (str[*index] == '\"')
	{
		if (!guill)
			guill = 1;
		else
			guill = 0;
	}
	if (str[*index] == '\'' && !guill)
	{
		if (!apost)
			apost = 1;
		else
			apost = 0;	
	}
	*dbquote = guill;
	*quote = apost;
	return (1);
}

void discard_backslash(char	*data, int *i, char **res)
{
	int backslash_nbr;
	int index;
	char *tmp;

	index = *i;
	backslash_nbr = 0;
	tmp = NULL;
	if (data[index] == '\\')
	{
		while (data[index] == '\\')
		{
			index++;
			backslash_nbr++;
		}
		backslash_nbr /= 2;
		tmp = ft_strsub(data, index - backslash_nbr, backslash_nbr);
		*i = index;
		*res = ft_strjoinf(*res, tmp, 4);	
	}
}

void expans_moica(char *data, int *index, int *expandu, char **res, t_core *shell)
{
	int i;

	i = *index;
	if (data[i] == '$' || data[i] == '~' || data[i] == '`')
	{
		*expandu = expelliarmus(data, &i, res, shell);
		if (!*expandu)
			i--;
	}
	*index = i;
}

char *infinite_expansion(char *data, t_core *shell)
{
	int flag[4];
	char *res;
	char *tmp;

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = -1;
	flag[3] = 1;
	tmp = NULL;
	res = ft_strnew(0);
	while (data[++flag[2]])
	{
		flag[3] = get_quotes_flags(data, &flag[2], &flag[0], &flag[1]);
		if (!flag[1])
		{
			expans_moica(data, &flag[2], &flag[3], &res, shell);
			discard_backslash(data, &flag[2], &res);
		}
		if (flag[3])
		{
			tmp = ft_strsub(data, flag[2], 1);
			res = ft_strjoinf(res, tmp, 4);
		}
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
