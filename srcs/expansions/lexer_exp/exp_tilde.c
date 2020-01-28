/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:14:15 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/28 19:09:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*exp_get_tilde(char *string, int len)
{
	(void)string;
	(void)len;
	/*
	char	*str;

	str = NULL;
	if (!ft_strncmp(string, "~", len))
	{
		if (!(str = ft_strsub(string, string, len)))
			return (NULL);
		return (str);
	}
	return (string);
	*/
	return (ft_strdup("~"));
}

char		*exp_get_tildep(char *string, int len)
{
	(void)string;
	(void)len;
	/*
	char	*str;

	str = NULL;
	if (!ft_strncmp(string, "~+", len))
	{
		if (!(str = ft_strsub(string, 0, len)))
			return (NULL);
		return (str)
	}
	return (string);*/
	return (ft_strdup("~+"));
}

char		*exp_get_tildem(char *string, int len)
{
	(void)string;
	(void)len;
	/*
	char	*str;

	str = NULL;
	if (!ft_strncmp(string, "~-", len))
	{
		if (!(str = ft_strsub(string, 0, len)))
			return (NULL);
		return (str);
	}
	return (string);*/
	return (ft_strdup("~-"));
}
