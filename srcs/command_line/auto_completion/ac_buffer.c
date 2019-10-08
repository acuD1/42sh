/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:30 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/08 13:02:21 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *path, char *name, t_read *input)
{
	uint64_t	value;
	char		buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	delete_last_cmd(*prev_b, input);
	if (is_dir(path) == TRUE)
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
			return (FALSE);
	}
	return (FALSE);
}

/* char			**split_env_var(char **env) */
/* { */
/* 	char			**var; */
/* 	int				i; */
/* 	int				j; */
/*  */
/* 	i = -1; */
/* 	var = ft_memalloc(sizeof(var) * ft_tablen(env)); */
/* 	while (env[++i]) */
/* 	{ */
/* 		j = 0; */
/* 		while (env[i][j] && env[i][j] != '=') */
/* 			j++; */
/* 		var[i] = ft_strsub(env[i], 0, j); */
/* 		var[i] = ft_strjoin("$", var[i]); */
/* 	} */
/* 	var[i] = 0; */
/* 	return (var); */
/* } */
/*  */
/* void			parse_env(char *prev_b, char *to_find, t_read *input) */
/* { */
/* 	char		**var; */
/* 	int		i; */
/* 	int		found; */
/*  */
/* 	(void)found; */
/* 	i = -1; */
/* 	var = split_env_var(input->env); */
/* 	while (var[++i]) */
/* 	{ */
/* 		if (isstart(var[i], to_find)) */
/* 		{ */
/* 			found = TRUE; */
/* 			if (read_again(&prev_b, NULL, var[i], input) == TRUE) */
/* 				continue ; */
/* 			else */
/* 			{ */
/* 				free(var); */
/* 				return ; */
/* 			} */
/* 		} */
/* 		if (i == ft_tablen(var) - 1) */
/* 			i = -1; */
/* 	} */
/* } */

uint8_t		get_dir(char *prev_b, char *to_find, char *current_dir)
{
	int	found;

	found = ft_strlen(to_find);
	while (to_find[--found])
	{
		if (to_find[found] == '/')
		{
			ft_bzero(current_dir, BUFF_SIZE);
			ft_strncpy(current_dir, prev_b, found + 1);
			to_find = ft_strrchr(to_find, '/') + 1;
			ft_bzero(prev_b, ft_strlen(prev_b));
			ft_strcpy(prev_b, to_find);
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
**		Reading data name off the current directory opened
**		Return FAILURE(-1) to stop reading (an error occured or no tab key pressed)
*/

uint8_t             read_dir(char **prev_b, char *to_find, t_read *input)
{
	char            current_dir[BUFF_SIZE];
	struct dirent   *data;
	uint8_t		found;
	DIR             *dir;
	char            *path;

	if (get_dir(*prev_b, to_find, current_dir))
		ft_strcpy(to_find, *prev_b);
	else if (getcwd(current_dir, BUFF_SIZE))
		ft_strcat(current_dir, "/");
	else
		return (FAILURE);
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			path = ft_strjoin(current_dir, data->d_name);
			if (read_again(prev_b, path, data->d_name, input) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				free(path);
				return (FAILURE);
			}
		}
	}
	//*prev_b = ft_strcat(current_dir, to_find);
	return (found);
}

/*
**		To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *prev_b, char *to_find, t_read *input)
{
	int				found;

	found = FALSE;
	/*
	 **		parse_env will be replace by intern_var list (2bcontinued)
	 */
	/* if (isstart(to_find, "$")) */
	/* { */
	/* 	parse_env(prev_b, to_find, input); */
	/* 	return ; */
	/* } */
	if ((found = read_dir(&prev_b, to_find, input)) == FAILURE)
		return ;
	found == TRUE ? to_complete_buffer(prev_b, to_find, input) : 0;
}
