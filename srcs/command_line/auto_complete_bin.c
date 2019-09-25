/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:38:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/25 18:29:59 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Split all bin/sbin directories in an array
*/

char			**split_path(char **env, char *str)
{
	char		**array;
	int			i;
	int			len;

	array = NULL;
	i = -1;
	while (env && env[++i])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		if (!ft_strncmp(str, env[i], len))
		{
			array = ft_strsplit(env[i] + len + 1, ":");
			break ;
		}
	}
	return (array);
}

/*
** Function to save in buffer the current bin found at buffer[0]
*/

void			insert_bin_in_buffer(char *d_name, t_read *input)
{
	int			i;
	int			buf_index;

	i = -1;
	buf_index = 0;
	ft_bzero(input->buffer, ft_strlen(input->buffer));
	while (d_name[++i])
	{
		insert_char_in_buffer(d_name[i], input, buf_index);
		buf_index++;
	}
}

/*
** Check if the buffer match with the current bin
** Return true if another tab key is pressed or no match found
*/

uint8_t			not_found(char *name, char *to_find, char *buf, t_read *input)
{
	uint64_t	value;

	if (isstart(name, to_find))
	{
		input->found = 1;
		goto_prompt(input);
		insert_bin_in_buffer(name, input);
		if (read(0, buf, READ_SIZE) > 0)
		{
			value = get_mask(buf);
			if (value == TAB_KEY)
				return (TRUE);
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

/*
** Open directories in the PATH variable
** Check if an exe bin already exists with the curr buffer inserted
*/

void			walking_path_var(char *buf, char *to_find, t_read *input)
{
	struct dirent	*data;
	DIR		*dir;
	char		**path;
	int		i;

	i = -1;
	path = split_path(input->env, "PATH");
	while (path && path[++i])
	{
		dir = opendir(path[i]);
		while ((data = readdir(dir)) != NULL)
		{
			if (not_found(data->d_name, to_find, buf, input))
				continue ;
			else
			{
				ft_tabfree(path);
				closedir(dir);
				return ;
			}
		}
		closedir(dir);
	}
	input->found == 1 ? walking_path_var(buf, to_find, input) : 0;
}
