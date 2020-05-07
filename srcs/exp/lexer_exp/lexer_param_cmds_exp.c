/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_param_cmds_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:46:13 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/09 19:21:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t		check_brackets_inbracket(u_int32_t *count, char c)
{
	u_int8_t dbq;

	dbq = 0;
	if (c == '$' )
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

char			*exp_get_bracket(const char *string, size_t len)
{
	char		*str;
	size_t		index;
	u_int32_t	count;

	index = 0;
	count = 0;
	str = NULL;
	if (!ft_strncmp(string, "${", len))
	{
		index = len;
		while (string[index])
		{
			index++;
		}
		index++;
		if (!(str = ft_strsub(string, 0, index)))
			return (NULL);
		printf("%s\n", str);
		return (str);
	}
	return (NULL);
}

static size_t	get_index_expan(const char *str)
{
	size_t	i;

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

char			*exp_get_dollar(const char *string, size_t len)
{
	char	*str;
	size_t	index;

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
