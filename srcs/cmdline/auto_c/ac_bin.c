/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:51 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:52:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>
#include <unistd.h>

/*
** 		Function to save in buffer the current bin found at buffer[0]
*/

static void		insert_bin_in_buffer(const char *bin, t_read *term)
{
	ssize_t buff_index;

	buff_index = term->x_index - term->prompt_len;
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(bin, term);
}

static void		add_builtin_lst(t_lst **bin, const char *cmd)
{
	static char	*blt_names[14] = {"set", "unset", "export", "exit", "cd"
	, "echo", "pwd", "type", "fg", "jobs", "bg", "hash", "fc", "test"};
	size_t		i;

	i = 0;
	while (i < 14)
	{
		if (!*cmd || ft_isstart(blt_names[i], cmd))
			ft_lstappend(&(*bin), ft_lstnew(blt_names[i],
							sizeof(char) * (ft_strlen(blt_names[i]) + 1)));
		i++;
	}
}

static u_int8_t	is_completion(t_read *term)
{
	u_int64_t	value;
	char		buff[READ_SIZE + 1];

	value = 0;
	ft_bzero(buff, READ_SIZE + 1);
	if (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY || value == 0x909000000000000)
			return (TRUE);
		else
			term->ac_tmp = ft_strdup(buff);
		ft_bzero(buff, READ_SIZE + 1);
	}
	return (FALSE);
}

/*
** 	Check if the buffer match with the current bin
** 	Return true if another tab key is pressed or no match found
*/

static void		display_bin(t_lst *bin, t_read *term)
{
	t_lst		*head;

	head = NULL;
	head = bin;
	while (bin)
	{
		goto_prompt(term);
		insert_bin_in_buffer(bin->content, term);
		if (is_completion(term) == TRUE)
		{
			if (!bin->next)
				bin = head;
			else
				bin = bin->next;
		}
		else
			break ;
	}
}

/*
** 	Open directories in the PATH variable
** 	Check if an exe bin already exists with the curr buffer inserted
*/

void			to_complete_bin(const char *to_find, t_read *term)
{
	struct dirent	*data;
	DIR				*dir;
	char			**path;
	ssize_t			i;
	t_lst			*bin;

	i = -1;
	bin = NULL;
	path = split_path(term->shell, "PATH");
	while (path && path[++i] && is_dir(path[i]))
	{
		dir = opendir(path[i]);
		while (dir && (data = readdir(dir)) != NULL)
		{
			if ((!*to_find || ft_isstart(data->d_name, to_find))
			&& is_a_blt(data->d_name) == -1 && !ft_isstart(data->d_name, "."))
				ft_lstappend(&bin, ft_lstnew(data->d_name,
							sizeof(char) * (ft_strlen(data->d_name) + 1)));
		}
		closedir(dir);
	}
	ft_tabfree(path);
	add_builtin_lst(&bin, to_find);
	display_bin(bin, term);
	free_lst(bin);
}
