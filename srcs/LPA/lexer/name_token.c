/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:15:08 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/12 15:38:08 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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

	if (!str[i])
		return (0);
	f[1] = (str[i] == '\"') ? 1 : 0;
	f[0] = (str[i] == '$' && str[i + 1] && str[i + 1] == '{') ? 1 : 0;
	while (str[++i])
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
	}
	return (i);
}

static void		check_all_quotes(char *str, size_t *index)
{
	size_t	i;

	i = *index;
	if (str[i] == '\\')
	{
		if (str[i + 1])
			i++;
	}
	else if (str[i] == '\'')
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

	index = 0;
	if (!str || !str[i])
		return (0);
	index = i;
	while (str[index])
	{
		check_all_quotes(str, &index);
		if ((index >= 1 && str[index - 1] != '\\')
			&& ft_strchr(CHAR_INTERRUPT, str[index]))
			break ;
		index++;
	}
	return (index);
}
