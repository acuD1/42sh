/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:45:32 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 06:25:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*exp_get_bquote(const char *string, int len)
{
	int			i;
	char		*str;

	i = 0;
	str = NULL;
	if (!ft_strncmp(string, "`", len))
	{
		i++;
		while (string[i])
		{
			if (string[i] == '`')
			{
				i++;
				break ;
			}
			i++;
		}
		if (!(str = ft_strsub(string, 0, i)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

static char		*new_exp(const char *string, enum e_estate id)
{
	int					i;
	char				*new;
	static t_lex_exp	lex_pex[] = {
		{exp_get_bquote, E_BQUOTE, 1},
		{exp_get_tildep, E_TILDEP, 2},
		{exp_get_tildem, E_TILDEM, 2},
		{exp_get_tilde, E_TILDE, 1},
		{exp_get_dbparen, E_DBPARENT, 3},
		{exp_get_paren, E_PARENT, 2},
		{exp_get_bracket, E_BRACKET, 2},
		{exp_get_hook, E_HOOK, 2},
		{exp_get_dollar, E_DOLLAR, 1},
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
	int					i;
	const t_exp_token	exp[] = {
		{E_BQUOTE, "`", 1},
		{E_TILDEP, "~+", 2},
		{E_TILDEM, "~-", 2},
		{E_TILDE, "~", 1},
		{E_DBPARENT, "$((", 3},
		{E_PARENT, "$(", 2},
		{E_BRACKET, "${", 2},
		{E_HOOK, "$[", 2},
		{E_DOLLAR, "$", 1},
		{NB_EXPANSION_STATE, NULL, 0}
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
	char		*new;

	new = NULL;
	if ((new = new_exp(string, state)))
		return (new);
	return (NULL);
}
