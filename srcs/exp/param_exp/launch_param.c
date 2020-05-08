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

	db_tmp = NULL;
	if (!(ft_strchr(str, '$') && str[0] != '$')
			&& (db_tmp = search_db(shell->env, str)))
	{
		ft_strdel(&str);
		return (ft_strdup(db_tmp->value));
	}
	shell->status = 1;
	ft_strdel(&str);
	return (NULL);
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

char				*exp_param(const char *data, t_core *shell)
{
	if (data[0] == '$' && data[1] == '{')
		return (get_brace_param((char*)data, shell));
	if (data[0] == '$' && data[1])
		return (simple_format(ft_strsub(data, 1, ft_strlen(data) - 1), shell));
	return (NULL);
}
