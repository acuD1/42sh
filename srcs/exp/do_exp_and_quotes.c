/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exp_and_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:35:57 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 05:47:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

enum e_estate	skip_quotes(const char *str, int *j, enum e_estate st)
{
	if (!str || ((str[*j] == '\"' && st == E_QUOTE)
		|| (str[*j] == '\'' && st == E_DBQUOTE)))
		return (st);
	if (str[*j] == '\"' && (st == E_DBQUOTE || st == NB_EXPANSION_STATE))
	{
		if (str[*j] == '\"')
			*j += 1;
		if (st == E_DBQUOTE)
			st = NB_EXPANSION_STATE;
		else if (st == NB_EXPANSION_STATE)
			st = E_DBQUOTE;
	}
	else if (str[*j] == '\'' && (st == E_QUOTE || st == NB_EXPANSION_STATE))
	{
		if (st == E_QUOTE)
			st = NB_EXPANSION_STATE;
		else if (st == NB_EXPANSION_STATE)
			st = E_QUOTE;
		if (str[*j] == '\'')
			*j += 1;
	}
	if (str[*j] == '\'' || str[*j] == '\"')
		st = skip_quotes(str, j, st);
	return (st);
}

char					*do_exp_et_quote(t_core *shell, const char *data)
{
	char	*exp;

	exp = NULL;
	if ((exp = do_expansion(shell, data)))
		return (exp);
	return (NULL);
}

void					init_expansionat(t_expansion *exp)
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

char					*do_expansion(t_core *shell, const char *data)
{
	char		*res;
	t_expansion	exp;

	init_expansionat(&exp);
	res = NULL;
	exp.erience = is_expansion(E_DBQUOTE);
	if (!exp.erience)
		return (ft_strdup(data));
	if ((res = exp.sionat[exp.erience](data, shell)))
		return (res);
	return (NULL);
}
