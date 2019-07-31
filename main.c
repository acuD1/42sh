/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:47:19 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/31 10:39:51 by arsciand         ###   ########.fr       */
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
	t_lst	**map;
	t_db	db;
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
	hash->db.bin = ft_strdup(key);
	hash->db.path = ft_strdup(path);
	return (&hash->db);
}

void	init_hash_map(t_hash *hash)
{
	hash->map = NULL;
	//hash->db->bin = NULL;
	//hash->db->path = NULL;
//	hash->db = NULL;
}
int		main(void)
{
	t_hash	hash;
	char	*line;
	size_t	i;
	int		fd;
	int		col = 0;
	int		c = 0;

	i = 0;
	line = NULL;
	init_hash_map(&hash);
	hash.map = ft_memalloc(sizeof(t_lst*) * HASH_SIZE);
	fd = open("words.txt.bak", O_RDONLY);
	while(ft_getnextline(fd, &line))
	{
		c++;
		if (ft_lstlen(hash.map[get_hash(line)]) > 0)
			col++;
		ft_lstappend(&hash.map[get_hash(line)], ft_lstnew(fetch(&hash, line, ""), sizeof(t_db)));
		free(line);
	}
	// PRINT
	while (i < HASH_SIZE)
	{
		int z = 0;
		while (hash.map[i])
		{
			if (z > 0)
				printf("\t");
			printf("[%zu][%d] BIN|%s| PATH|%s|\n", i, z,
				((t_db*)(hash.map[i]->content))->bin,
				((t_db*)(hash.map[i]->content))->path);
			hash.map[i] = hash.map[i]->next;
			z++;
		}
		i++;
	}
	printf("\nCOLLISION\n\n[%d] %0.2f %c\n\nLOAD FACTOR\n\n%0.2f\n\n", col, (float)(col * 100) / HASH_SIZE, '%', (float)c / HASH_SIZE);
	if (((float)c / HASH_SIZE) > 0.75)
		printf("RESZIE NEEDED");
	//
	close(fd);
	return (0);
}
