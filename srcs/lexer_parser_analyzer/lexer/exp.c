/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:37:09 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 17:37:14 by guvillat         ###   ########.fr       */
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

char	*new_exp(char *string, e_pstate id)
{
	int					i;
	char 				*new;
	static t_lex_exp	lex_pex[] = {
		{exp_get_tildep, P_TILDEP ,2},
		{exp_get_tildem, P_TILDEM,2},
		{exp_get_tilde, P_TILDE ,1},
		{exp_get_dbparen, P_DBPARENT,3},
		{exp_get_paren, P_PARENT,2},
		{exp_get_bracket, P_BRACKET,2},
		{exp_get_hook, P_HOOK, 2},
		{exp_get_dollar, P_DOLLAR, 1},
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

e_pstate find_expansion(char *str)
{
	const	t_token	exp[] = 	{
									{P_TILDEP, "~+", 2},
									{P_TILDEM, "~-", 2},
									{P_TILDE, "~", 1},
									{P_DBPARENT, "$((", 3},
									{P_PARENT, "$(", 2},
									{P_BRACKET, "${", 2},
									{P_HOOK, "$[", 2},
									{P_DOLLAR, "$", 1},
									{P_EXP_INTERRUPT, NULL, 0}
								};
	int 				i;

	i = 0;
	while (exp[i].id != P_EXP_INTERRUPT)
	{
		if (!ft_strncmp(str, exp[i].data, exp[i].len))
			return (exp[i].id);
		i++;
	}
	return (P_EXP_INTERRUPT);
}

char	*get_expansion(char *string, e_pstate state)
{
	char *new;

	new = NULL;
	if ((new = new_exp(string, state)))
		return (new);
	return (NULL);
}
