/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:30 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/02 16:52:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *buff, char *name, t_read *input)
{
	uint64_t	value;

	delete_last_cmd(*prev_b, input);
	if (is_dir(name) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, input);
	if (xread(0, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY)
		{
			*prev_b = name;
			return (TRUE);
		}
		else
		{
			check_caps(buff, input);
			return (FALSE);
		}
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
	char		**var;
	int		i;
	int		found;

	(void)found;
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
				free(var);
				return ;
			}
		}
		if (i == ft_tablen(var) - 1)
			i = -1;
	}
}

/*
**		Reading data name off the current directory opened
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

	/* found = ft_strlen(to_find); */
	/* printf("[%s]\n", to_find, ft_strlen(to_find)); */
	/* while (to_find[--found]) */
	/* { */
	/* 	if (to_find[found] == '/') */
	/* 	{ */
	/* 		ft_bzero(current_dir, BUFF_SIZE); */
	/* 		ft_strncpy(current_dir, prev_b, found + 1); */
	/* 		to_find = ft_strrchr(to_find, '/') + 1; */
	/* 		ft_bzero(prev_b, ft_strlen(prev_b)); */
	/* 		ft_strcpy(prev_b, saved); */
	/* 	} */
	/* } */
	/* printf("[%s]\n", current_dir); */
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
	/*
	**		parse_env will be replace by intern_var list (2bcontinued)
	*/
	if (isstart(to_find, "$"))
	{
		parse_env(buf, prev_b, to_find, input);
		return ;
	}
	if ((found = read_dir(buf, &prev_b, to_find, input)) == FAILURE)
		return ;
	found == TRUE ? to_complete_buffer(buf, prev_b, to_find, input) : 0;
}
