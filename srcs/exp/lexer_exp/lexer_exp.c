/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:45:32 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/08 20:23:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*new_exp(const char *string, enum e_estate id)
{
	size_t				i;
	char				*new;
	static t_lex_exp	lex_pex[5] = {
		{exp_get_tildep, E_TILDEP, "", 2},
		{exp_get_tildem, E_TILDEM, "", 2},
		{exp_get_tilde, E_TILDE, "", 1},
		{exp_get_bracket, E_BRACKET, "", 2},
		{exp_get_dollar, E_DOLLAR, "", 1},
	};

	i = 0;
	new = NULL;
	while (i < NB_OF_EXP)
	{
		if (id == lex_pex[i].id)
			if ((new = lex_pex[i].fct(string, lex_pex[i].len)))
				return (new);
		i++;
	}
	return (NULL);
}

enum e_estate	find_expansion(const char *str)
{
	size_t				i;
	const t_exp_token	exp[6] = {
		{"~+", E_TILDEP, "", 2},
		{"~-", E_TILDEM, "", 2},
		{"~", E_TILDE, "", 1},
		{"${", E_BRACKET, "", 2},
		{"$", E_DOLLAR, "", 1},
		{NULL, NB_EXPANSION_STATE, "", 0}
	};

	i = 0;
	while (exp[i].id != NB_EXPANSION_STATE)
	{
		if (!ft_strncmp(str, exp[i].data, exp[i].len))
			return (exp[i].id);
		i++;
	}
	return (NB_EXPANSION_STATE);
}

char			*get_expansion(const char *string, enum e_estate state)
{
	char	*new;

	new = NULL;
	if ((new = new_exp(string, state)))
		return (new);
	return (NULL);
}
