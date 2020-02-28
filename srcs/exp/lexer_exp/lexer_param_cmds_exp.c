/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_param_cmds_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:46:13 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 05:34:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*exp_get_paren(const char *string, int len)
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

int		check_brackets_inbracket(int *count, char c)
{
	if (c == '{')
		*count += 1;
	if (c == '}')
	{
		if (*count)
			*count -= 1;
		else
			return (0);
	}
	return (1);
}

char			*exp_get_bracket(const char *string, int len)
{
	char		*str;
	int			index;
	int			count; 

	index = 0;
	count = 0;
	str = NULL;
	if (!ft_strncmp(string, "${", len))
	{
		index = len;
		while (string[index])
		{
			if (!check_brackets_inbracket(&count, string[index]))
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

static int8_t	get_index_expan(const char *str)
{
	int		i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[1] == '?' || str[1] == '$'
			|| str[1] == '!' || str[1] == '-'
			|| str[1] == '@' || str[1] == '*')
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

char			*exp_get_dollar(const char *string, int len)
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
