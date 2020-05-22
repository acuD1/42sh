/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 00:38:22 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/14 17:06:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**		Split all bin/sbin directories in an array
*/

char			**split_path(t_core *shell, const char *str)
{
	char	**array;
	t_lst	*env;

	env = shell->env;
	array = NULL;
	while (env)
	{
		if (!ft_strcmp(str, ((t_db*)(env->content))->key))
		{
			array = ft_strsplit(((t_db*)(env->content))->value, ":");
			break ;
		}
		env = env->next;
	}
	return (array);
}

static char		*parse_path(char *input)
{
	char		*path;
	ssize_t		len;

	path = ft_strdup(input);
	len = (ssize_t)ft_strlen(input) - 1;
	while (len > 0 && path[len])
	{
		if (path[len - 1] == '/')
		{
			path[len] = '\0';
			break ;
		}
		len--;
	}
	return (path);
}

char			*get_dir_path(t_auto_comp *ac, char *input, char **path)
{
	char		*cmd;

	cmd = NULL;
	if (input == NULL || !*input)
	{
		*path = ft_strdup("./");
		cmd = ft_strdup("./");
	}
	else if (*input != '/')
	{
		cmd = ft_strjoin("./", input);
		*path = parse_path(cmd);
		ac->x += ft_strlen(*path) - 2;
	}
	else
	{
		cmd = ft_strdup(input);
		*path = parse_path(cmd);
		ac->x += ft_strlen(*path);
	}
	return (cmd);
}
