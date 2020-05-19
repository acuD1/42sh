/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:43:26 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/16 17:42:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			get_prompt_value(t_core *shell, const char *key)
{
	t_db	*db;

	db = NULL;
	if (key == NULL || (db = search_db(shell->env, key)) == NULL)
	{
		shell->term.prompt = ft_strnew(0);
		return ;
	}
	if (!ft_strcmp(db->value, PS1))
		shell->term.prompt = ft_strsub(db->value, 1, 10);
	else if (!ft_strcmp(db->value, PS2))
		shell->term.prompt = ft_strsub(db->value, 1, 2);
	else
		shell->term.prompt = ft_strdup(db->value);
}

char			*get_home_value(t_core *shell)
{
	t_db	*db;
	char	*path;

	db = NULL;
	path = NULL;
	if ((db = search_db(shell->env, "HOME")) == NULL)
		return (path = ft_strdup(HISTORY_FILE));
	else if (!is_dir(db->value))
		return (path = ft_strdup(HISTORY_FILE));
	else
	{
		path = ft_strjoin(db->value, "/");
		path = ft_strjoinf(path, HISTORY_FILE, 1);
	}
	return (path);
}
