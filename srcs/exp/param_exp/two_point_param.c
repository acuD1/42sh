/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_opt.c                                    :+:      :+:    :+:   */
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
	char	*word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	word = check_env_key(&tablo[1][1], shell);
	ft_tabfree(tablo);
	return (ft_strdup(word));
}

char		*plus_format(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		word = check_env_key(&tablo[1][1], shell);
		ft_tabfree(tablo);
		return (ft_strdup(word));
	}
	ft_tabfree(tablo);
	return (NULL);
}

char		*egal_format(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	add_assign_env(shell, tablo[0], &tablo[1][1]);
	word = ft_strdup(&tablo[1][1]);
	ft_tabfree(tablo);
	return (word);
}

char		*underniercaspourlaroute(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	value = check_env_key(tablo[0], shell);
	word = NULL;
	if (value && *value)
	{
		word = check_env_key(tablo[1], shell);
		if (!word || !*word)
		{
			ft_tabfree(tablo);
			return (ft_strdup(value));
		}
		else
			return (error_moar_format_third(tablo, word));
	}
	ft_tabfree(tablo);
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
