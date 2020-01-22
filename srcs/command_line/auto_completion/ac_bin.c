/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:51 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/22 13:47:04 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** 	Function to save in buffer the current bin found at buffer[0]
*/

void			insert_bin_in_buffer(char *d_name, t_read *term)
{
	int			i;
	int			buf_index;

	i = -1;
	buf_index = 0;
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE);
	while (d_name[++i])
	{
		insert_char_in_buffer(d_name[i], term, buf_index);
		buf_index++;
	}
}

/*
** 	Check if the buffer match with the current bin
** 	Return true if another tab key is pressed or no match found
*/

uint8_t			not_found(char *name, char *to_find, t_read *term)
{
	uint64_t	value;
	char		buff[READ_SIZE + 1];

	value = 0;
	ft_bzero(buff, READ_SIZE);
	if (isstart(name, to_find))
	{
		term->flag = TRUE;
		goto_prompt(term);
		insert_bin_in_buffer(name, term);
		if (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
		{
			value = get_mask(buff);
			if (value == TAB_KEY)
				return (TRUE);
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

/*
** 	Open directories in the PATH variable
** 	Check if an exe bin already exists with the curr buffer inserted
*/

void			to_complete_bin(char *to_find, t_read *term)
{
	struct dirent	*data;
	DIR				*dir;
	char			**path;
	int				i;

	i = -1;
	path = split_path(term->shell, "PATH");
	while (path && path[++i])
	{
		dir = opendir(path[i]);
		while ((data = readdir(dir)) != NULL)
		{
			if (not_found(data->d_name, to_find, term))
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
	ft_tabfree(path);
	term->flag == TRUE ? to_complete_bin(to_find, term) : 0;
}
