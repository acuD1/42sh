/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:24 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/04 20:47:26 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		get_quote_flag(char *str, int *index, int *dbquote, int *quote)
{
	if (str[*index] == '\"')
	{
		if (!*dbquote)
			*dbquote = 1;
		else
			*dbquote = 0;
	}
	if (str[*index] == '\'' && !*dbquote)
	{
		if (!*quote)
			*quote = 1;
		else
			*quote = 0;
	}
	return (1);
}

void			discard_backslash(char *data, int *i, char **res)
{
	int			backslash_nbr;
	int			index;
	char		*tmp;

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

void			sortilege_dexpansion(char *data,
	int flag[4], char **res, t_core *shell)
{
	int			i;

	i = flag[2];
	if (data[i] == '$' || data[i] == '~' || data[i] == '`')
	{
		flag[3] = expelliarmus(data, &i, res, shell);
		if (!flag[3])
			i--;
	}
	flag[2] = i;
}

void			init_infinite_flags(int flag[4])
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = -1;
	flag[3] = 1;
}

char			*infinite_expansion(char *data, t_core *shell)
{
	int			flag[4];
	char		*res;
	char		*tmp;

	init_infinite_flags(flag);
	tmp = NULL;
	res = ft_strnew(0);
	while (data[++flag[2]])
	{
		flag[3] = get_quote_flag(data, &flag[2], &flag[0], &flag[1]);
		if (!flag[1])
		{
			sortilege_dexpansion(data, flag, &res, shell);
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
