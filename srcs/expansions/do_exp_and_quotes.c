/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exp_and_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:35:57 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/04 19:35:59 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static e_estate	gla_quote(char *str, int *j, e_estate state)
{
	if ((str[*j] == '\"' && state == E_QUOTE)
		|| (str[*j] == '\'' && state == E_DBQUOTE))
		return (state);
	if (str[*j] == '\"' && (state == E_DBQUOTE || state == NB_EXPANSION_STATE))
	{
		if (str[*j] == '\"')
			*j += 1;
		if (state == E_DBQUOTE)
			state = NB_EXPANSION_STATE;
		else if (state == NB_EXPANSION_STATE)
			state = E_DBQUOTE;
	}
	if (str[*j] == '\'' && (state == E_QUOTE || state == NB_EXPANSION_STATE))
	{
		if (state == E_QUOTE)
			state = NB_EXPANSION_STATE;
		else if (state == NB_EXPANSION_STATE)
			state = E_QUOTE;
		if (str[*j] == '\'')
			*j += 1;
	}
	if (str[*j] == '\'' || str[*j] == '\"')
		gla_quote(str, j, state);
	return (state);
}

char			*quote_mechanisms(char *str)
{
	char		*new;
	int			i;
	int			j;
	e_estate	state;

	j = 0;
	i = 0;
	new = NULL;
	if (!str)
		return (NULL);
	new = ft_strnew(ft_strlen(str));
	state = NB_EXPANSION_STATE;
	i = 0;
	while (str[j])
	{
		state = gla_quote(str, &j, state);
		if (!str[j])
			break ;
		new[i] = str[j];
		i++;
		j++;
	}
	ft_strdel(&str);
	return (new);
}

char			*do_exp_et_quote(t_core *shell, char *data)
{
	char		*exp;
	char		*unquoted;

	exp = NULL;
	unquoted = NULL;
	if ((exp = do_expansion(shell, data)))
		if ((unquoted = quote_mechanisms(exp)))
			return (unquoted);
	return (NULL);
}

void			init_expansionat(t_expansion *exp)
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

char			*do_expansion(t_core *shell, char *data)
{
	char		*res;
	t_expansion exp;

	init_expansionat(&exp);
	res = NULL;
	exp.erience = is_expansion(E_DBQUOTE);
	if (!exp.erience)
		return (ft_strdup(data));
	if ((res = exp.sionat[exp.erience](data, shell)))
		return (res);
	return (NULL);
}
