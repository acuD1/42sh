/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:51 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/30 18:10:13 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>
#include <unistd.h>

static void		add_builtin_lst(t_auto_comp *ac, const char *cmd)
{
	static char	*blt_names[14] = {"set ", "unset ", "export ", "exit ", "cd "
	, "echo ", "pwd ", "type ", "fg ", "jobs ", "bg ", "hash ", "fc ", "test "};
	size_t		i;

	i = 0;
	while (i < 14)
	{
		if (!*cmd || ft_isstart(blt_names[i], cmd))
		{
			ft_lstappend(&ac->lst, ft_lstnew(blt_names[i],
							sizeof(char) * (ft_strlen(blt_names[i]) + 1)));
			ac->max_len = get_max_len(ac->max_len, ft_strlen(blt_names[i]));
			ac->lst_size++;
		}
		i++;
	}
}

static void		fill_bin_lst(char *input, t_auto_comp *ac, char **path)
{
	struct dirent	*data;
	char			*tmp;
	DIR				*dir;
	ssize_t			i;

	i = -1;
	tmp = NULL;
	while (path[++i] && is_dir(path[i]))
	{
		dir = opendir(path[i]);
		while (dir && (data = readdir(dir)) != NULL)
		{
			if ((!*input || ft_isstart(data->d_name, input))
			&& is_a_blt(data->d_name) == -1 && !ft_isstart(data->d_name, "."))
			{
				tmp = ft_strjoin(data->d_name, " ");
				ft_lstappend(&ac->lst, ft_lstnew(tmp,
						sizeof(char) * (ft_strlen(tmp) + 1)));
				ac->lst_size++;
				ac->max_len = get_max_len(ac->max_len, ft_strlen(tmp));
				ft_strdel(&tmp);
			}
		}
		closedir(dir);
	}
}

/*
** 	Open directories in the PATH variable
** 	Check if an exe bin already exists with the curr buffer inserted
*/

void			ac_binary(char *input, t_auto_comp *ac, t_core *shell)
{
	char			**path;

	ac->ws_col = (size_t)shell->term.ws_col;
	if ((path = split_path(shell, "PATH")) != NULL)
	{
		fill_bin_lst(input, ac, path);
		ft_tabfree(path);
	}
	add_builtin_lst(ac, input);
	if (ac->lst_size == 0)
		ac_file(input, ac, shell);
}
