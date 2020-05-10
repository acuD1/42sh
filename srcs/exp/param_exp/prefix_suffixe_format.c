/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffixe_format.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:47 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/08 20:24:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*smallest_suffix_param(char *value, char *pattern)
{
	size_t	pattern_size;

	pattern_size = 0;
	if (!value)
		return (ft_strdup(pattern));
	if (ft_strlen(value) >= ft_strlen(pattern))
		pattern_size = ft_strlen(value) - ft_strlen(pattern);
	if (ft_strequ(value + pattern_size, pattern))
		return (ft_strsub(value, 0, pattern_size));
	return (ft_strdup(value));
}

char		*suffix_format(char *data, t_core *shell)
{
	char		*str[3];
	char		**tablo;

	str[2] = NULL;
	str[1] = NULL;
	tablo = ft_strsplit(data, "%");
	str[0] = check_env_key(tablo[0], shell);
	if (str[0] && *str[0])
	{
		if (tablo[1])
		{
			str[1] = inhibiteurs_expansion(tablo[1], shell, 0);
			str[2] = smallest_suffix_param(str[0], str[1]);
			ft_strdel(&str[1]);
		}
		else
			str[2] = ft_strdup(str[0]);
	}
	ft_tabfree(tablo);
	ft_strdel(&data);
	return (str[2]);
}

static char	*smallest_prefix_param(char *value, char *pattern)
{
	size_t	size;

	size = 0;
	if (!value)
		return (ft_strdup(pattern));
	size = ft_strlen(pattern);
	if (ft_strnequ(value, pattern, size))
		return (ft_strsub(value, (unsigned int)size, ft_strlen(value) - size));
	return (ft_strdup(value));
}

char		*prefix_format(char *data, t_core *shell)
{
	char		**tablo;
	char		*str[3];

	str[2] = NULL;
	str[1] = NULL;
	tablo = ft_strsplit(data, "#");
	str[0] = check_env_key(tablo[0], shell);
	if (str[0] && *str[0])
	{
		if (tablo[1])
		{
			str[1] = inhibiteurs_expansion(tablo[1], shell, 0);
			str[2] = smallest_prefix_param(str[0], str[1]);
			ft_strdel(&str[1]);
		}
		else
			str[2] = ft_strdup(str[0]);
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (str[2]);
}
