/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:36:49 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 17:36:52 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*exp_get_paren(char *string, int len)
{
	char	*str;
	int		index;

	str = NULL;
	index = 0;
	if (!ft_strncmp(string, "$(", len))
	{
		while (string[index])
		{
			if (string[index] == ')')
				break ;
			index++;
		}
		index++;
		if (!(str = ft_strsub(string, 0, index)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

char		*exp_get_bracket(char *string, int len)
{
	char	*str;
	int		index;

	index = 0;
	str = NULL;
	if (!ft_strncmp(string, "${", len))
	{
		index = len;
		while (string[index] && string[index] != '}')
			index++;
		index++;
		if (!(str = ft_strsub(string, 0, index)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

int8_t		get_index_expan(char *str)
{
	int i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '?')
		{
			i++;
			break ;
		}
		if (!(str[i] == '_' || ft_isdigit(str[i])
			|| ft_isalpha(str[i])))
			break ;
		i++;
	}
	return (i);
}

char		*exp_get_dollar(char *string, int len)
{
	char	*str;
	int		index;

	index = len;
	str = NULL;
	if (string[0] == '$')
	{
		index = get_index_expan(string);
		if (!(str = ft_strsub(string, 0, index)))
			return (NULL);
		return (str);
	}
	return (NULL);
}

char		*exp_get_tilde(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~", len))
	// {
	// 	// if (!(str = ft_strsub(string, string, len)))
	// 	// 	return (NULL);
	// 	// return (str);
	// }
	// return (string);
	return (ft_strdup("~"));
}

char		*exp_get_tildep(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~+", len))
	// {
	// 	if (!(str = ft_strsub(string, 0, len)))
	// 		return (NULL);
	// 	return (str)
	// }
	// return (string);
	return (ft_strdup("~+"));
}

char		*exp_get_tildem(char *string, int len)
{
	// char	*str;
	(void)string;
	(void)len;
	// str = NULL;
	// if (!ft_strncmp(string, "~-", len))
	// {
	// 	if (!(str = ft_strsub(string, 0, len)))
	// 		return (NULL);
	// 	return (str);
	// }
	// return (string);
	return (ft_strdup("~-"));
}
