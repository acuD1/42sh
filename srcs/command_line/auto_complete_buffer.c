/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:48:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/09 15:56:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *buf, char *name, t_read *input)
{
	delete_last_cmd(*prev_b, input);
	if (is_dir(name) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, input);
	if (xread(0, buf, READ_SIZE) > 0)
	{
		if (buf[0] == TAB_KEY)
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
	char			**var;
	int				i;
	int				j;

	i = -1;
	var = ft_memalloc(sizeof(var) * ft_tablen(env));
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		var[i] = ft_strsub(env[i], 0, j);
		var[i] = ft_strjoin("$", var[i]);
	}
	var[i] = 0;
	return (var);
}

void			parse_env(char *buf, char *prev_b, char *to_find, t_read *input)
{
	char			**var;
	int				i;
	int				found;

	i = -1;
	var = split_env_var(input->env);
	while (var[++i])
	{
		if (isstart(var[i], to_find))
		{
			found = TRUE;
			if (read_again(&prev_b, buf, var[i], input) == TRUE)
				continue ;
			else
			{
				ft_tabfree(var);
				return ;
			}
		}
		if (i == ft_tablen(var) - 1)
			i = -1;
	}
}

/*
**		Reading data name of the current directory opened
**		Return FAILURE(-1) to stop reading (an error occured or no tab key pressed)
*/

uint8_t			read_dir(char *buf, char **prev_b, char *to_find, t_read *input)
{
	char			current_dir[BUFF_SIZE];
	struct dirent	*data;
	uint8_t			found;
	DIR				*dir;

	if (!getcwd(current_dir, BUFF_SIZE))
		return (FAILURE);
	/* if (ft_strchr(to_find, '/')) */
	/* { */
	/* 	char *tmp = ft_strchr(to_find, '/') + 1; */
	/* 	ft_strcat(current_dir, "/"); */
	/* 	ft_strncat(current_dir, to_find, strlen_to(to_find, '/')); */
	/* 	to_find = tmp; */
	/* 	prev_b = &tmp; */
	/* } */
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			if (read_again(prev_b, buf, data->d_name, input) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				return (FAILURE);
			}
		}
	}
	return (found);
}

/*
**		To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *buf, char *prev_b, char *to_find, t_read *input)
{
	int				found;

	found = FALSE;
	if (isstart(to_find, "$"))
	{
		parse_env(buf, prev_b, to_find, input);
		return ;
	}
	if ((found = read_dir(buf, &prev_b, to_find, input)) == FAILURE)
		return ;
	found == TRUE ? to_complete_buffer(buf, prev_b, to_find, input) : 0;
}
