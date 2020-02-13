/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 05:32:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*moar_format_plz(char *data, t_core *shell)
{
	char		**tablo;
	int			tablen;

	tablo = NULL;
	tablen = 0;
	if (data[ft_strlen(data) - 1] == ':')
		return (error_moar_format_bis(data));
	if ((tablo = ft_strsplit(data, ":")))
	{
		tablen = ft_tablen(tablo);
		if (tablen > 3)
			return (error_moar_format_param(tablo, data));
		else if (tablen == 3)
		{
			if (ft_strisdigit(tablo[1]) && ft_strisdigit(tablo[2]))
			{
				ft_strdel(&data);
				return (double_two_point_param(tablo, shell));
			}
		}
		else if (tablen == 2)
		{
			ft_strdel(&data);
			return (get_two_point_param_exp(tablo, shell));
		}
	}
	ft_dprintf(STDERR_FILENO, "42sh: %s : mauvaise substitution\n", tablo[0]);
	ft_tabfree(tablo);
	ft_strdel(&data);
	return (NULL);
}

char			*simple_format(char *str, t_core *shell)
{
	t_db		*db_tmp;

	db_tmp = NULL;
	if ((db_tmp = search_db(shell->env, str)))
	{
		ft_strdel(&str);
		return (ft_strdup(db_tmp->value));
	}
	ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
	ft_strdel(&str);
	return (NULL);
}

char			*format_supplementaires(char *str, t_core *shell)
{
	int			i;

	i = 0;
	if (str[0] == ':' || str[0] == '%' || str[0] == '$')
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		return (NULL);
	}
	if (str[i] == '#')
		return (length_format(str, shell));
	while (str[i])
	{
		if (str[i] == ':')
			return (moar_format_plz(str, shell));
		else if (str[i] == '%')
			return (suffix_format(str, shell));
		else if (str[i] == '#')
			return (prefix_format(str, shell));
		i++;
	}
	return (simple_format(str, shell));
}

static char		*get_brace_param(const char *str, t_core *shell)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '\n')
			ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		if (str[i] == '}')
			break ;
	}
	if (!(tmp = ft_strsub(str, 2, i - 2)))
		return (NULL);
	return (format_supplementaires(tmp, shell));
}

char			*exp_param(const char *data, t_core *shell)
{
	char		*tmp;

	tmp = NULL;
	if (data[0] == '$' && data[1] == '{')
		return (tmp = get_brace_param(data, shell));
	else if (data[0] == '$')
	{
		tmp = ft_strsub(data, 1, ft_strlen(data) - 1);
		return (simple_format(tmp, shell));
	}
	return (NULL);
}
