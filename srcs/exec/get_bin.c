/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/27 16:47:33 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>
#include <sys/stat.h>

/*
**	get_bin locate tokens[0] in the PATH variable with get_bin_path or set it as a
**	local with his absolut path.
*/


static char	*get_bin_path(char **path, const char *file)
{
	DIR				*content;
	struct dirent	*dir;
	size_t			i;

	i = 0;
	/*
	**	the path variable is a table of absolut binary path from PATH env
	*/
	while (path[i])
	{
		/*
		**	We check for each path if we can find the file.
		**	If so, we return the correct path.
		*/
		if (!(content = opendir(path[i])))
			continue;
		while (content && (dir = readdir(content)))
		{
			if (ft_strequ(file, dir->d_name))
			{
				closedir(content);
				return (ft_strdup(path[i]));
			}
			continue;
		}
		closedir(content);
		i++;
	}
	return (NULL);
}

char		*get_bin(t_core *shell, t_lst *env)
{
	struct stat	stat;
	char		**path;

	path = NULL;
	/*
	**	Severals test here :
	**	- if tokens[0] is a file
	**	- if tokens[0] is not NULL 		//Not sure if we need it
	**	- if tokens[0] is not only a "."
	*/
	if ((lstat(shell->tokens[0], &stat) == 0 && S_ISDIR(stat.st_mode))
		|| !shell->tokens[0]
		|| (shell->tokens[0][0] == '.' && !shell->tokens[0][1]))
		return (NULL);

	/*
	**	We set the shell->bin variable if tokens[0] is a local binary here
	*/
	if ((shell->tokens[0][0] == '.'
		|| shell->tokens[0][0] == '/') && shell->tokens[0][1])
		return (shell->bin = ft_strdup(shell->tokens[0]));

	/*
	**	HASH_TABLE
	*/
	// hash module call

	/*
	**	If not local, we're going to find it in PATH
	*/
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->key, "PATH") == TRUE)
		{

			/* PATH splited by ":" */
			path = ft_strsplit(((t_db*)(env->content))->value, ":");

			/* set correct path if the binary is found in PATH */
			shell->bin = ft_strjoinf(get_bin_path(path, shell->tokens[0]),
								ft_strjoin("/", shell->tokens[0]), FREE_ALL);

			ft_tabdel(&path);
		}
		env = env->next;
	}
	return (shell->bin);
}
