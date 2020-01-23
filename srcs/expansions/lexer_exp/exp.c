/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:13:53 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/14 16:13:59 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*exp_get_dbparen(char *string, int len)
{
	char				*str;
	int					index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(string, "$((", len))
	{
		index = len;
		while (string[index])
		{
			if (string[index] == ')')
			{
				if (string[index + 1] && string[index + 1] != ')')
					return (NULL);
				else
					break ;
			}
			index++;
		}
		if (!(str = ft_strsub(string, 0, index + 2)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

char	*exp_get_hook(char *string, int len)
{
	char				*str;
	int					index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(string, "$[", len))
	{
		while (string[index])
		{
			if (string[index] == ']')
				break ;
			index++;
		}
		if (!(str = ft_strsub(string, 0, index + 1)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

char	*new_exp(char *string, e_estate id)
{
	int					i;
	char 				*new;
	static t_lex_exp	lex_pex[] = {
		// {exp_get_bquote, E_BQUOTE ,1},
		{exp_get_tildep, E_TILDEP ,2},
		{exp_get_tildem, E_TILDEM,2},
		{exp_get_tilde, E_TILDE ,1},
		{exp_get_dbparen, E_DBPARENT,3},
		{exp_get_paren, E_PARENT,2},
		{exp_get_bracket, E_BRACKET,2},
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

e_estate find_expansion(char *str)
{
	const	t_exp_token	exp[] = 	{
		{E_BQUOTE, "'", 1},
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
	int 				i;

	i = 0;
	while (exp[i].id != NB_EXPANSION_STATE)
	{
		if (!ft_strncmp(str, exp[i].data, exp[i].len))
			return (exp[i].id);
		i++;
	}
	return (NB_EXPANSION_STATE);
}

char	*get_expansion(char *string, e_estate state)
{
	char *new;

	new = NULL;
	if ((new = new_exp(string, state)))
		return (new);
	return (NULL);
}
