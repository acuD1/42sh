/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffixe_format.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:47 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/11 15:29:48 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*smallest_suffix_param(char *value, char *pattern)
{
	int		pattern_size;

	if (!pattern || !value)
		return (NULL);
	pattern_size = ft_strlen(value) - ft_strlen(pattern);
	if (ft_strequ(value + pattern_size, pattern))
		return (ft_strsub(value, 0, pattern_size));
	return (ft_strdup(value));
}

char		*suffix_format(char *data, t_core *shell)
{
	char	*tmp;
	char	*value;
	char	**tablo;
	char	*resultat;

	tmp = NULL;
	value = NULL;
	resultat = NULL;
	tablo = NULL;
	if ((tmp = ft_strchr(data, '%')))
	{
		tablo = ft_strsplit(data, "%");
		value = check_env_key(tablo[0], shell);
		if (value && *value)
		{
			if (!tablo[1])
				resultat = ft_strdup(value);
			else if (tablo[1][0] == '$')
			{
				if (tablo[1][1] != '{')
					tmp = check_env_key(&tablo[1][1], shell);
				else
					tmp = get_brace_param(tablo[1], shell);
				resultat = smallest_suffix_param(value, tmp);
			}
			else
				resultat = smallest_suffix_param(value, tablo[1]);
		}
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}

static char		*smallest_prefix_param(char *value, char *pattern)
{
	int		size;

	if (!pattern || !value)
		return (NULL);
	size = ft_strlen(pattern);
	if (ft_strnequ(value, pattern, size))
		return (ft_strsub(value, size, ft_strlen(value) - size));
	return (ft_strdup(value));
}

char		*prefix_format(char *data, t_core *shell)
{
	char	*tmp;
	char	*value;
	char	**tablo;
	char	*resultat;

	tmp = NULL;
	value = NULL;
	resultat = NULL;
	tablo = NULL;
	if ((tmp = ft_strchr(data, '#')))
	{
		tablo = ft_strsplit(data, "#");
		value = check_env_key(tablo[0], shell);
		if (value && *value)
		{
			if (!tablo[1])
				resultat = ft_strdup(value);
			else if (tablo[1][0] == '$')
			{
				if (tablo[1][1] != '{')
					tmp = check_env_key(&tablo[1][1], shell);
				else
					tmp = get_brace_param(tablo[1], shell);
				resultat = smallest_prefix_param(value, tmp);
			}
			else
				resultat = smallest_prefix_param(value, tablo[1]);
		}
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}
