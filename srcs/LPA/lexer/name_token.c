/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:15:08 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 17:00:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

static size_t	loop_till_quote(const char *str, size_t index, char quote)
{
	index++;
	if (!str[index])
		return (index);
	while (str[index])
	{
		if (str[index] == quote)
			break ;
		index++;
	}
	return (index);
}

static size_t	loop_till_next_subprompt(const char *str, size_t i)
{
	size_t	f[2];

	f[1] = (str[i] == '\"') ? 1 : 0;
	f[0] = (str[i] == '$' && str[i + 1] && str[i + 1] == '{') ? 1 : 0;
	i++;
	while (str[i])
	{
		if (check_backslash_nbr((char*)str, (ssize_t*)&i))
			continue ;
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '{')
			f[0]++;
		else if (str[i] == '}' && f[0] && (!f[1] || f[0] > f[1]))
			f[0]--;
		else if (str[i] == '\"')
		{
			if (!f[1] || f[0] > f[1])
				f[1]++;
			else
				f[1]--;
		}
		if (!f[1] && !f[0])
			break ;
		i++;
	}
	return (i);
}

static void		check_all_quotes(char *str, size_t *index)
{
	size_t	i;

	i = *index;
	if (str[i] == '\'')
		i = loop_till_quote(str, i, '\'');
	else if (str[i] == '`')
		i = loop_till_quote(str, i, '`');
	else if ((str[i] == '$' && str[i + 1] && str[i + 1] == '{')
		|| str[i] == '\"')
		i = loop_till_next_subprompt(str, i);
	*index = i;
}

size_t			get_word_size_ntype(size_t i, char *str)
{
	size_t	index;
	size_t	f;

	index = 0;
	f = 0;
	if (!str || !str[i])
		return (0);
	index = i;
	while (str[index])
	{
		if (check_backslash_nbr(str, (ssize_t*)&index))
		{
			f = 1;
			index++;
			continue ;
		}
		check_all_quotes(str, &index);
		if (!f && ft_strchr(CHAR_INTERRUPT, str[index]))
			break ;
		f = 0;
		index++;
	}
	return (index);
}
