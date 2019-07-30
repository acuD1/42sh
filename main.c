/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:47:19 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/30 16:37:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared_libft.h"
#include "define.h"
#include <stdio.h>
//#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/types.h>

typedef struct s_db
{
	char	*bin;
	char	*path;
}			t_db;

typedef struct s_hash
{
	t_lst	**table;
	t_db	*db;
}				t_hash;

u_int32_t	get_hash(char *line)
{
	u_int32_t hash = 0;
	size_t i = 0;
	while (i < ft_strlen(line))
	{
		hash = ((hash << 8) + line[i]) % HASH_SIZE;
		i++;
	}
	return (hash);
}

t_db	*fetch(t_hash *hash, const char *key, const char *path)
{
	hash->db->bin = ft_strdup(key);
	hash->db->path = ft_strdup(path);
	return (hash->db);
}
int		main(void)
{
	t_hash	hash;
	t_db	db;
	char	*line;
	size_t	i;
	int		fd;
	int		col = 0;

	i = 0;
	line = NULL;
	hash.table = ft_memalloc(sizeof(t_lst*) * HASH_SIZE);
	fd = open("words.txt.bak", O_RDONLY);
	while(ft_getnextline(fd, &line))
	{
		if (hash.table[get_hash(line)] && hash.table[get_hash(line)]->next)
			col++;
		ft_lstappend(&hash.table[get_hash(line)], ft_lstnew(fetch(&hash, line, ""), sizeof(t_db)));
		free(line);
	}
	// PRINT
	while (i < HASH_SIZE)
	{
		int z = 0;
		while (hash.table[i])
		{
			if (z > 0)
				printf("\t");
			printf("[%zu][%d] BIN|%s| PATH|%s|\n", i, z,
				((t_db*)(hash.table[i]->content))->bin,
				((t_db*)(hash.table[i]->content))->path);
			hash.table[i] = hash.table[i]->next;
			z++;
		}
		i++;
	}
	printf("\nCOLLISION\n\n[%d] %0.2f %c\n\nLOAD FACTOR\n\n%0.2f\n\n", col, (float)(col * 100) / HASH_SIZE, '%', (float)466551 / HASH_SIZE);
	//
	close(fd);
	return (0);
}
