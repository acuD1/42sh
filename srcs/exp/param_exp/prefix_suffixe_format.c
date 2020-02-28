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
	int			pattern_size;
	char		*tmp;

	if (!pattern || !value)
		return (NULL);
	tmp = NULL;
	pattern_size = ft_strlen(value) - ft_strlen(pattern);
	if (ft_strequ(value + pattern_size, pattern))
	{
		tmp = ft_strsub(value, 0, pattern_size);
		ft_strdel(&value);
		return (tmp);
	}
	tmp = ft_strdup(value);
	ft_strdel(&value);
	return (tmp);
}

char			*suffix_format(char *data, t_core *shell)
{
	char		*value;
	char		**tablo;
	char		*resultat;

	resultat = NULL;
	tablo = ft_strsplit(data, "%");
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		if (!tablo[1])
			resultat = ft_strdup(value);
		else if (tablo[1] && tablo[1][0] == '$')
		{
			value = exp_param(tablo[1], shell);
			resultat = smallest_suffix_param(value, tablo[1]);
			ft_strdel(&value);
		}
		else
			resultat = smallest_suffix_param(ft_strdup(value), tablo[1]);
	}
	ft_tabfree(tablo);
	ft_strdel(&data);
	return (resultat);
}

static char		*smallest_prefix_param(char *value, char *pattern)
{
	int			size;
	char		*tmp;

	if (!pattern || !value)
		return (NULL);
	tmp = NULL;
	size = ft_strlen(pattern);
	if (ft_strnequ(value, pattern, size))
	{
		tmp = ft_strsub(value, size, ft_strlen(value) - size);
		ft_strdel(&value);
		return (tmp);
	}
	tmp = ft_strdup(value);
	ft_strdel(&value);
	return (tmp);
}

char			*prefix_format(char *data, t_core *shell)
{
	char		*value;
	char		**tablo;
	char		*resultat;

	resultat = NULL;
	tablo = ft_strsplit(data, "#");
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		if (!tablo[1])
			resultat = ft_strdup(value);
		else if (tablo[1] && tablo[1][0] == '$')
		{
			value = exp_param(tablo[1], shell);
			resultat = smallest_suffix_param(value, tablo[1]);
			ft_strdel(&value);
		}
		else
			resultat = smallest_prefix_param(ft_strdup(value), tablo[1]);
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}
