/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/03 11:33:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
		{
			i++;
			continue;
		}
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
	char		**split_path;
	char		*path;

	split_path = NULL;
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
	**	HASH_TABLE : Locate token[0] in the hash_map first, if found retourn the path found !
	*/
	//print_hash_map(&shell->hash);							//Shows error with valgrind ??
	if (locate_hash(shell, &shell->hash) == SUCCESS)
		return (shell->bin);

	/*
	**	If not local, we're going to find it in PATH
	*/
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->key, "PATH") == TRUE)
		{

			/* PATH splited by ":" */
			split_path = ft_strsplit(((t_db*)(env->content))->value, ":");
			path = get_bin_path(split_path, shell->tokens[0]);

			/* set correct path if the binary is found in PATH */
			shell->bin = ft_strjoinf(path , ft_strjoin("/", shell->tokens[0]),
							FREE_ALL);

			/* insert hash to hashmap, NOT PROTECTED */
			add_hash_map(shell, &shell->hash);
			ft_tabdel(&split_path);
		}
		env = env->next;
	}
	return (shell->bin);
}
