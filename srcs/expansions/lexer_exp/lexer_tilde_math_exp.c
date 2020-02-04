/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tilde_math_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:46:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/04 20:46:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*exp_get_tilde(char *string, int len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~"));
}

char		*exp_get_tildep(char *string, int len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~+"));
}

char		*exp_get_tildem(char *string, int len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~-"));
}

char		*exp_get_hook(char *string, int len)
{
	char	*str;
	int		index;

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

char		*exp_get_dbparen(char *string, int len)
{
	char	*str;
	int		index;

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
