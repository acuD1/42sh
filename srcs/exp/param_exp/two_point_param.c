/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_param_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 00:16:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/05 00:16:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*dash_format(char **tablo, t_core *shell)
{
	char	*value;
	int		i;

	i = 1;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
	}
	ft_tabfree(tablo);
	return (value);
}

char		*plus_format(char **tablo, t_core *shell)
{
	char	*value;

	value = NULL;
	if ((check_env_key(tablo[0], shell)))
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
		ft_tabfree(tablo);
		return (value);
	}
	ft_tabfree(tablo);
	return (NULL);
}

char		*egal_format(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;
	int		i;

	i = 1;
	word = NULL;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
		add_assign_env(shell, tablo[0], value);
	}
	ft_tabfree(tablo);
	return (value);
}

char		*underniercaspourlaroute(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	value = NULL;
	word = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{

		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else
			word = check_env_key(tablo[1], shell);
		if (!word || !*word)
		{
			ft_tabfree(tablo);
			return (ft_strdup(value));
		}
		else
			return (error_moar_format_third(tablo, word, shell));
	}
	ft_tabfree(tablo);
	return (NULL);
}

char			*moar_format_plz(char *data, t_core *shell)
{
	char		**tablo;
	int			tablen;

	tablo = NULL;
	tablen = 0;
	if (data[ft_strlen(data) - 1] == ':')
		return (error_moar_format_bis(data, shell));
	if ((tablo = ft_strsplit(data, ":")))
	{
		tablen = ft_tablen(tablo);
		if (tablen > 3)
			return (error_moar_format_param(tablo, data, shell));
		else if ((tablen == 3) && ft_strisdigit(tablo[1]) && ft_strisdigit(tablo[2]))
		{
			ft_strdel(&data);
			return (double_two_point_param(tablo, shell));
		}
		else if (tablen == 2)
		{
			ft_strdel(&data);
			return (get_two_point_param_exp(tablo, shell));
		}
	}
	ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", tablo[0]);
	ft_tabfree(tablo);
	ft_strdel(&data);
	shell->status = 1;
	return (NULL);
}

char		*get_two_point_param_exp(char **tablo, t_core *shell)
{
	if (tablo[1][0] == '-')
		return (dash_format(tablo, shell));
	else if (tablo[1][0] == '+')
		return (plus_format(tablo, shell));
	else if (tablo[1][0] == '=')
		return (egal_format(tablo, shell));
	else if (tablo[1][0] == '?')
		return (questionmark_format(tablo, shell));
	else
		return (underniercaspourlaroute(tablo, shell));
	ft_tabfree(tablo);
	return (NULL);
}
