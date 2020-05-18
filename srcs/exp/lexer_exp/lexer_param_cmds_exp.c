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

char			*exp_get_bracket(const char *s, size_t len)
{
	char		*str;
	size_t		i;

	str = NULL;
	i = len;
	i = loop_till_next_subprompt(s, 0);
	if (!(str = ft_strsub(s, 0, i + 1)))
		return (NULL);
	return (str);
}

size_t			get_index_expan(const char *str)
{
	size_t	i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[1] == '?' || str[1] == '$'
			|| str[1] == '!' || str[1] == '-' || str[1] == '#'
			|| str[1] == '@' || str[1] == '*' || ft_isdigit(str[1]))
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
