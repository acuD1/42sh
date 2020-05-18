/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

char				*tilde_param_exp(char *tablo, t_core *shell)
{
	char	*tmp;

	tmp = NULL;
	tmp = exp_tilde(&tablo[1], shell);
	if (!check_tilde_path_exp(tmp, tablo, 1))
	{
		if (tablo[1] == '~' && (tablo[2] == '-' || tablo[2] == '+'))
			tmp = ft_strjoinf(tmp, &tablo[3], 1);
		else
			tmp = ft_strjoinf(tmp, &tablo[2], 1);
	}
	return (tmp);
}

char				*simple_format(char *str, t_core *shell)
{
	t_db	*db_tmp;
	char	*res;

	db_tmp = NULL;
	res = NULL;
	if (!(ft_strchr(str, '$') && str[0] != '$')
			&& (db_tmp = search_db(shell->env, str)))
		res = ft_strdup(db_tmp->value);
	ft_strdel(&str);
	return (res);
}

char				*format_supplementaires(char *str, t_core *shell)
{
	size_t	i;

	i = 0;
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

char				*moar_format_plz(char *data, t_core *shell)
{
	char	*tablo[2];
	size_t	i;

	i = 0;
	tablo[0] = NULL;
	tablo[1] = NULL;
	while (data[i] != ':')
		i++;
	tablo[0] = ft_strsub(data, 0, i);
	i++;
	tablo[1] = ft_strsub(data, (unsigned int)i, ft_strlen(data) - i);
	ft_strdel(&data);
	if (tablo[1][0] == '-')
		return (dash_format(tablo, shell));
	else if (tablo[1][0] == '+')
		return (plus_format(tablo, shell));
	else if (tablo[1][0] == '=')
		return (egal_format(tablo, shell));
	else if (tablo[1][0] == '?')
		return (questionmark_format(tablo, shell));
	return (NULL);
}

char				*exp_param(const char *str, t_core *shell)
{
	if (str[0] == '$' && str[1] == '{')
		return (get_brace_param((char*)str, shell));
	else if (str[0] == '$' && str[1] && is_pos_vars(str[1]))
		return (pos_vars_format(ft_strsub(str, 1, 1), shell));
	else if (str[0] == '$' && str[1])
		return (simple_format(ft_strsub(str, 1, get_index_expan(str)), shell));
	return (NULL);
}
