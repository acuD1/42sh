/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:24 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 06:35:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	get_quote_flag
	(const char *str, int *index, int *dbquote, int *quote)
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

int		discard_backslash(const char *data, int *i, char **res)
{
	int		backslash_nbr;
	int		index;
	int		ret;
	char	*tmp;

	index = *i;
	backslash_nbr = 0;
	tmp = NULL;
	ret = 0;
	if (data[index] == '\\')
	{
		while (data[index] == '\\')
		{
			index++;
			backslash_nbr++;
		}
		ret = backslash_nbr % 2;
		backslash_nbr /= 2;
		tmp = ft_strsub(data, index - backslash_nbr, backslash_nbr);
		if (data[index] == '\n')
			index++;
		*i = index;
		*res = ft_strjoinf(*res, tmp, 4);
	}
	return (ret);
}

static void	check_if_we_shall_exp
	(const char *data, int flag[5], char **res, t_core *shell)
{
	int		i;

	i = flag[2];
	if ((data[i] == '$' || data[i] == '~' || data[i] == '`'))
	{
		flag[3] = get_exp(data, &i, res, shell);
		if (!flag[3])
			i--;
	}
	flag[2] = i;
}

static void	init_infinite_flags
	(int flag[5], char **tmp, char **resultat, enum e_estate *state)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = -1;
	flag[3] = 1;
	flag[4] = 0;
	*resultat = ft_strnew(0);
	*tmp = NULL;
	*state = NB_EXPANSION_STATE;
}

char		*quote_backslash_discarder(const char *data)
{
	char			*res;
	char			*tmp;
	int				index;
	enum e_estate	st;

	st = NB_EXPANSION_STATE;
	if (!data)
		return (NULL);
	tmp = NULL;
	res = NULL;
	index = 0;
	while (data[index])
	{
		st = skip_quotes(data, &index, st);
		if (!data[index])
			break ;
		if (st != E_QUOTE)
			discard_backslash(data, &index, &res);
		if (res)
		{
			tmp = ft_strsub(data, index, 1);
			res = ft_strjoinf(res, tmp, 4);
		}
		else
			res = ft_strsub(data, index, 1);
		index++;
	}
	return (res);
}

char		*infinite_expansion(const char *data, t_core *shell)
{
	int				flag[5];
	char			*res;
	char			*tmp;
	enum e_estate	st;

	if (!data || !*data)
		return (NULL);
	init_infinite_flags(flag, &tmp, &res, &st);
	while (data[++flag[2]])
	{
		flag[3] = get_quote_flag(data, &flag[2], &flag[0], &flag[1]);
		st = skip_quotes(data, &flag[2], st);
		if (!data[flag[2]])
			break ;
		if (!flag[1])
			if (!discard_backslash(data, &flag[2], &res))
				check_if_we_shall_exp(data, flag, &res, shell);
		st = skip_quotes(data, &flag[2], st);
		if (!data[flag[2]])
			break ;
		if (flag[3])
		{
			tmp = ft_strsub(data, flag[2], 1);
			res = ft_strjoinf(res, tmp, 4);
		}
	}
	return (res);
}
