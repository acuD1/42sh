/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:51 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/26 10:26:40 by arsciand         ###   ########.fr       */
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
	ft_bzero(term->buffer, ft_strlen(term->buffer));
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

uint8_t			not_found(char *name, char *to_find, char *buf, t_read *term)
{
	uint64_t	value;

	if (isstart(name, to_find))
	{
		term->found = 1;
		goto_prompt(term);
		insert_bin_in_buffer(name, term);
		if (xread(STDIN_FILENO, buf, READ_SIZE) > 0)
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
** 	Open directories in the PATH variable
** 	Check if an exe bin already exists with the curr buffer inserted
*/

void			to_complete_bin(char *buf, char *to_find, t_read *term)
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
			if (not_found(data->d_name, to_find, buf, term))
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
	term->found == 1 ? to_complete_bin(buf, to_find, term) : 0;
}
