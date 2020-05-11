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

static u_int8_t	exit_condi(const char *str, size_t i, size_t *db, size_t *br)
{
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '{')
		*db += 1;
	else if (str[i] == '}' && *db && (!*br || *db > *br))
		*db -= 1;
	else if (str[i] == '\"')
	{
		if (!*br || *db > *br)
			*br += 1;
		else
			*br -= 1;
	}
	if (!*br && !*db)
		return (0);
	return (1);
}

size_t			loop_till_next_subprompt(const char *str, size_t i)
{
	size_t	f[2];

	f[1] = (str[i] == '\"') ? 1 : 0;
	f[0] = (str[i] == '$' && str[i + 1] && str[i + 1] == '{') ? 1 : 0;
	i++;
	while (str[i])
	{
		if (check_backslash_nbr((char*)str, (ssize_t*)&i))
			continue ;
		if (str[i] == '\'' && f[0] > f[1])
			i = loop_till_quote(str, i, '\'');
		if (!exit_condi(str, i, &f[0], &f[1]))
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
	size_t	index[3];

	if (!str || !str[i])
		return (0);
	index[0] = i;
	index[2] = ft_strlen(str);
	while (index[0] < index[2] && str[index[0]])
	{
		index[1] = 0;
		if (check_backslash_nbr(str, (ssize_t*)&index[0]))
		{
			index[1] = 1;
			if (index[0] >= index[2])
				break ;
			index[0]++;
			continue ;
		}
		check_all_quotes(str, &index[0]);
		if (!index[1] && ft_strchr(CHAR_INTERRUPT, str[index[0]]))
			break ;
		index[0]++;
	}
	return (index[0]);
}
