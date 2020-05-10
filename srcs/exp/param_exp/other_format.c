/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:12 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

char		*questionmark_format(char **tablo, t_core *shell)
{
	char	*value;

	value = check_env_key(tablo[0], shell);
	if (value && *value != '\0')
	{
		ft_strdel(&tablo[0]);
		ft_strdel(&tablo[1]);
		return (ft_strdup(value));
	}
	else if (!tablo[1][1] && (!value || !*value))
		ft_dprintf(STDERR_FILENO,
			"42sh : %s parameter null or not set\n", tablo[0]);
	else
	{
		if (tablo[1])
			value = inhibiteurs_expansion(&tablo[1][1], shell, 0);
		ft_dprintf(STDERR_FILENO, "42sh: %s: %s\n", tablo[0], value);
		ft_strdel(&value);
	}
	shell->subst_error = 1;
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	return (NULL);
}

char		*dash_format(char **tablo, t_core *shell)
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
		value = inhibiteurs_expansion(&tablo[1][1], shell, 0);
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	return (value);
}

char		*length_format(char *str, t_core *shell)
{
	t_db	*db_tmp;

	db_tmp = NULL;
	if (ft_strchr(str, ':') || ft_strchr(str, '%') || ft_strchr(&str[1], '#')
		|| str[2] == '~')
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		ft_strdel(&str);
		shell->subst_error = 1;
		return (NULL);
	}
	if ((db_tmp = search_db(shell->env, &str[1])))
	{
		ft_strdel(&str);
		return (ft_itoa((int32_t)ft_strlen(db_tmp->value)));
	}
	ft_strdel(&str);
	return (ft_strdup("0"));
}

char		*plus_format(char **tablo, t_core *shell)
{
	char	*value;

	value = NULL;
	if ((check_env_key(tablo[0], shell)))
	{
		if (tablo[1])
			value = inhibiteurs_expansion(&tablo[1][1], shell, 0);
		ft_strdel(&tablo[0]);
		ft_strdel(&tablo[1]);
		return (value);
	}
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	return (NULL);
}

char		*egal_format(char **tablo, t_core *shell)
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
		value = inhibiteurs_expansion(&tablo[1][1], shell, 0);
		add_assign_env(shell, tablo[0], value);
	}
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	return (ft_strdup(value));
}
