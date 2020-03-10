/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:35:57 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/10 14:32:39 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

enum e_estate	skip_recur_quote(char *str, size_t *index, enum e_estate st)
{
	if (!str || (str[*index] == '\\')
		|| ((str[*index] == '\"' && st == E_QUOTE)
		|| (str[*index] == '\'' && st == E_DBQUOTE)))
		return (st);
	if (str[*index] == '\"' && (st == E_DBQUOTE || st == NB_EXPANSION_STATE))
	{
		if (st == E_DBQUOTE)
			st = NB_EXPANSION_STATE;
		else if (st == NB_EXPANSION_STATE)
			st = E_DBQUOTE;
		if (str[*index] == '\"')
			*index += 1;
	}
	else if (str[*index] == '\'' && (st == E_QUOTE || st == NB_EXPANSION_STATE))
	{
		if (st == E_QUOTE)
			st = NB_EXPANSION_STATE;
		else if (st == NB_EXPANSION_STATE)
			st = E_QUOTE;
		if (str[*index] == '\'')
			*index += 1;
	}
	if (str[*index] == '\'' || str[*index] == '\"')
		st = skip_recur_quote(str, index, st);
	return (st);
}

enum e_estate	skip_quotes(char *str, t_expansion *exp)
{
	if (str[exp->index] == '\"'
		&& (exp->quotus == E_DBQUOTE || exp->quotus == NB_EXPANSION_STATE))
	{
		if (exp->quotus == E_DBQUOTE)
			exp->quotus = NB_EXPANSION_STATE;
		else if (exp->quotus == NB_EXPANSION_STATE)
			exp->quotus = E_DBQUOTE;
		if (str[exp->index] == '\"')
			exp->index += 1;
	}
	else if (str[exp->index] == '\''
		&& (exp->quotus == E_QUOTE || exp->quotus == NB_EXPANSION_STATE))
	{
		if (exp->quotus == E_QUOTE)
			exp->quotus = NB_EXPANSION_STATE;
		else if (exp->quotus == NB_EXPANSION_STATE)
			exp->quotus = E_QUOTE;
		if (str[exp->index] == '\'')
			exp->index += 1;
	}
	return (exp->quotus);
}

u_int32_t		discard_backslash(const char *data, size_t *i, char **res)
{
	size_t		index;
	u_int32_t	b_nbr;
	u_int32_t	ret;
	char		*tmp;

	index = *i;
	b_nbr = 0;
	tmp = NULL;
	ret = 0;
	if (data[index] == '\\')
	{
		while (data[index] == '\\')
		{
			index++;
			b_nbr++;
		}
		ret = b_nbr % 2;
		b_nbr /= 2;
		tmp = ft_strsub(data, (unsigned int)(index - b_nbr), (size_t)b_nbr);
		*res = ft_strjoinf(*res, tmp, 4);
		if (data[index] == '\n')
			index++;
		*i = index;
	}
	return (ret);
}

t_expansion		*quotes_biteurs(char *data, t_core *shell, t_expansion *exp)
{
	exp->quotus = skip_quotes(data, exp);
	exp->st = (!data[exp->index]) ? E_END : E_START;
	(void)shell;
	return (exp);
}

t_expansion		*discard_biteurs(char *dt, t_core *shell, t_expansion *exp)
{
	(void)shell;
	exp->discarded = discard_backslash(dt, &(exp->index), &(exp->res));
	exp->st = (!dt[exp->index]) ? E_END : E_START;
	return (exp);
}
