/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:38:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/26 14:43:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/twenty_one.h"

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
			array = ft_strsplit(env[i] + len + 1, ':');
			break ;
		}
	}
	return (array);
}

/*
** Function to save in buffer the current bin found at buffer[0]
** ToDo: check if the buffer is right
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
** Open directories in the PATH variable
** Check in each one if an exe bin already exists with the current buffer inserted
** ToDo: recursive function
*/
void				walking_path_var(char **env, char *buf, t_read *input)
{
	struct dirent 	*data;
	DIR				*dir;
	char			**path;
	char			*tmp;
	int				i;

	i = -1;
	path = split_path(env, "PATH");
	tmp = ft_strdup(input->buffer);
	while (path && path[++i])
	{
		dir = opendir(path[i]);
		while ((data = readdir(dir)) != NULL)
		{
			if (isstart(data->d_name, tmp))
			{
				goto_prompt(input);
				insert_bin_in_buffer(data->d_name, input);
				if (read(0, buf, 5) > 0)
					if (buf[0] == '\t')
						continue ;
				ft_strdel(&tmp);
				ft_tabfree(path);
				closedir(dir);
				return ;
			}
		}
	}
}
