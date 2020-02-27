/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_param_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:12 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/11 15:29:17 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*check_env_key(char *key, t_core *shell)
{
	t_db	*db;

	db = search_db(shell->env, key);
	if (db)
		return (db->value);
	return (NULL);
}

char		*questionmark_format(char **tablo, t_core *shell)
{
	char *value;
	char *word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			word = check_env_key(&tablo[1][2], shell);
		else
			word = ft_strdup(&tablo[1][1]);
		ft_dprintf(STDERR_FILENO,
			"42sh: %s: %s\n", tablo[0], word);
	}
	else
		ft_dprintf(STDERR_FILENO,
			"42sh: %s parameter null or not set\n", tablo[0]);
	ft_tabfree(tablo);
	return (NULL);
}

char		*length_format(char *str, t_core *shell)
{
	t_db	*db_tmp;

	db_tmp = NULL;
	if (ft_strchr(str, ':') || ft_strchr(str, '%') || ft_strchr(&str[1], '#'))
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		ft_strdel(&str);
		return (NULL);
	}
	if ((db_tmp = search_db(shell->env, &str[1])))
	{
		ft_strdel(&str);
		return (ft_itoa(ft_strlen(db_tmp->value)));
	}
	ft_strdel(&str);
	return (ft_strdup("0"));
}

char		*double_two_point_param(char **tablo, t_core *shell)
{
	int		flag[3];
	char	*tmp[2];

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	tmp[0] = NULL;
	tmp[1] = check_env_key(tablo[0], shell);
	if (tmp[1])
	{
		flag[1] = ft_strlen(tmp[1]) - 1;
		if ((flag[2] = ft_atoi(tablo[2])) < 0)
			flag[2] = flag[1];
		if ((flag[0] = ft_atoi(tablo[1])) < 0)
		{
			ft_tabfree(tablo);
			return (NULL);
		}
		if (!(tmp[0] = ft_strsub(tmp[1], flag[0], flag[2])))
			return (NULL);
	}
	ft_tabfree(tablo);
	return (tmp[0]);
}
