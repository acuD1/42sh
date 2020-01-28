/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/28 20:20:42 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t	is_expansion(enum e_estate id)
{
	if (id == E_TILDEP)
		return (1);
	else if (id == E_TILDEM)
		return (2);
	else if (id == E_TILDE)
		return (3);
	else if (id == E_DBPARENT)
		return (4);
	else if (id == E_PARENT || id == E_BQUOTE)
		return (5);
	else if (id == E_BRACKET)
		return (6);
	else if (id == E_HOOK)
		return (7);
	else if (id == E_DOLLAR)
		return (8);
	else if (id == E_DBQUOTE)
		return (9);
	else if (id == E_QUOTE)
		return (0);
	return (0);
}

char		*no_exp(char *data, t_core *shell)
{
	(void)shell;
	(void)data;
	printf("COMMENT CA SE FESSE\n");
	return (NULL);
}

// Heu WTF ? ^^
int			expelliarmus(char *src, int *index, char **dst, t_core *shell)
{
	t_expansion		toto;
	enum e_estate	state;
	char			*hetero;
	char			*trans;
	int				i;

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

static int	get_quotes_flags(char c, int *dbquote, int *quote)
{
	int		guill;
	int		apost;

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
	return (1);
}

char		*exp_dbquote(char *data, t_core *shell)
{
	int		flag[4];
	char	*res;
	char	*tmp;

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 1;
	tmp = NULL;
	res = ft_strnew(0);
	while (data[flag[2]])
	{
		flag[3] = get_quotes_flags(data[flag[2]], &flag[0], &flag[1]);
		if (!flag[1]
			&& (data[flag[2]] == '$'
			|| data[flag[2]] == '~' || data[flag[2]] == '`'))
		{
			flag[3] = expelliarmus(data, &flag[2], &res, shell);
			if ((size_t)flag[2] == ft_strlen(data))
				break ;
			if (!flag[3])
				flag[2]--;
		}
		if (flag[3])
		{
			tmp = ft_strsub(data, flag[2], 1);
			res = ft_strjoinf(res, tmp, 4);
		}
		flag[2]++;
	}
	return (res);
}

void		expansion(t_core *shell, t_process *process)
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
