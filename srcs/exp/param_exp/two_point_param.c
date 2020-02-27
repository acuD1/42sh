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
	int		i;

	word = NULL;
	i = 1;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1] && tablo[1][1] == '$')
		i++;
	if ((value = check_env_key(&tablo[1][i], shell)))
		word = ft_strdup(value);
	else
		word = ft_strdup(&tablo[1][1]);
	ft_tabfree(tablo);
	return (word);
}

char		*plus_format(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	word = NULL;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		if (tablo[1][1] == '$')
		{
			word = check_env_key(&tablo[1][2], shell);
			ft_tabfree(tablo);
			if (!word)
				return (NULL);
		}
		else
			word = ft_strdup(&tablo[1][1]);
		ft_tabfree(tablo);
		return (word);
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
	if (tablo[1][1] == '$')
	{
		value = check_env_key(&tablo[1][2], shell);
		if (value)
		{
			word = ft_strdup(value);
			add_assign_env(shell, tablo[0], word);
		}
	}
	else
	{
		word = ft_strdup(&tablo[1][1]);
		add_assign_env(shell, tablo[0], word);
	}
	ft_tabfree(tablo);
	return (word);
}

char		*underniercaspourlaroute(char **tablo, t_core *shell)
{
	char	*value;
	char	*word;

	value = NULL;
	word = NULL;
	if ((value = check_env_key(tablo[0], shell)))
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
