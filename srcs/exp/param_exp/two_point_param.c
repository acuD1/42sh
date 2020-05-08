/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_point_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 00:16:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/09 19:26:28 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_two_point_param_exp(char **tablo, t_core *shell)
{
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

char	*egal_format(char **tablo, t_core *shell)
{
	char	*value;

	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_strdel(&tablo[0]);
		ft_strdel(&tablo[1]);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else if (tablo[1][1] == '~')
			value = tilde_param_exp(tablo[1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
		add_assign_env(shell, tablo[0], value);
	}
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	return (ft_strdup(value));
}

char	*moar_format_plz(char *data, t_core *shell)
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
	tablo[1] = ft_strsub(data, i, ft_strlen(data) - i);
	ft_strdel(&data);
	return (get_two_point_param_exp(tablo, shell));
}
