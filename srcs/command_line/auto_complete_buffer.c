/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:48:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/05 17:02:07 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**	Delete last command insert in buffer and insert the new one
**	Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *buf, char *name, t_read *input)
{
	delete_last_cmd(*prev_b, input);
	if (is_dir(name) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, input);
	if (xread(0, buf, READ_SIZE) > 0)
	{
		if (buf[0] == '\t')
		{
			*prev_b = name;
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}


char			**split_env_var(char **env)
{
	char		**var;
	int		i;
	int		j;

	i = -1;
	var = ft_memalloc(sizeof(var) * ft_tablen(env));
	while (env && env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		var[i] = ft_strsub(env[i], 0, j);
		var[i] = ft_strjoin("$", var[i]);
	}
	var[i] = '\0';
	return (var);
}

void			to_complete_env_var(char *buf, char *last_buf, char *to_find, t_read *input)
{
	char		**var;
	int		i;
	int		found;

	i = -1;
	var = split_env_var(input->env);
	while (var && var[++i])
	{
		if (isstart(var[i], to_find + 1))
		{
			found = TRUE;
			if (read_again(&last_buf, buf, var[i], input) == TRUE)
				continue ;
			else
			{
				ft_tabfree(var);
				return ;
			}
		}
	}
	ft_tabfree(var);
	found == TRUE ? to_complete_env_var(buf, last_buf, to_find, input) : 0;
}

/*
** To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *buf, char *last_buf,
						char *to_find, t_read *input)
{
	struct dirent	*data;
	DIR		*dir;
	char		current_dir[BUFF_SIZE];
	int		found;

	/* if (isstart(to_find, "$")) */
	/* { */
	/* 	to_complete_env_var(buf, last_buf, to_find, input); */
	/* 	return ; */
	/* } */
	if (!getcwd(current_dir, BUFF_SIZE))
		return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			if (read_again(&last_buf, buf, data->d_name, input) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				return ;
			}
		}
	}
	found == TRUE ? to_complete_buffer(buf, last_buf, to_find, input) : 0;
}
