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

enum e_estate	skip_recur_quote(char *str, int *index, enum e_estate st)
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
	if (str[exp->index] == '\"' && (exp->quotus == E_DBQUOTE || exp->quotus == NB_EXPANSION_STATE))
	{
		if (exp->quotus == E_DBQUOTE)
			exp->quotus = NB_EXPANSION_STATE;
		else if (exp->quotus == NB_EXPANSION_STATE)
			exp->quotus = E_DBQUOTE;
		if (str[exp->index] == '\"')
			exp->index += 1;
	}
	else if (str[exp->index] == '\'' && (exp->quotus == E_QUOTE || exp->quotus == NB_EXPANSION_STATE))
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

void					init_expansion_machine(t_expansion *exp)
{
	exp->sionat[0] = no_exp;
	exp->sionat[1] = exp_tilde;
	exp->sionat[2] = exp_tilde;
	exp->sionat[3] = exp_tilde;
	exp->sionat[4] = exp_math;
	exp->sionat[5] = exp_cmd_subs;
	exp->sionat[6] = exp_param;
	exp->sionat[7] = exp_math;
	exp->sionat[8] = exp_param;
}
