/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:47:19 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/02 14:26:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared_libft.h"
#include "define.h"
#include <stdio.h>
//#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/types.h>

typedef struct	s_db
{
	char		*bin;
	char		*path;
}				t_db;

typedef struct	s_hash
{
	t_lst		**map;
	t_db		db;
	u_int32_t	size;
	int			col;
	int			count;
}				t_hash;

u_int32_t	get_hash(char *line, u_int32_t size)
{
	size_t		i;
	u_int32_t	hash;

	i = 0;
	hash = 0;
	while (i < ft_strlen(line))
	{
		hash = ((hash << 8) + line[i]) % size;
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
	hash->col = 0;
	hash->count = 0;
	hash->size	= HASH_SIZE;
	hash->db.bin = NULL;
	hash->db.path = NULL;
}

void	fill_hash_map(t_hash *hash)
{
	int		fd;
	char	*line;
	u_int32_t value;

	line = NULL;
	fd = open("words.txt", O_RDONLY);
	while(ft_getnextline(fd, &line))
	{
		value = get_hash(line, hash->size);
		hash->count++;
		if (ft_lstlen(hash->map[value]) > 0)
			hash->col++;
		ft_lstappend(&hash->map[value], ft_lstnew(fetch(hash, line, "test"), sizeof(t_db)));
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
}

void	free_hash_map(t_hash *hash)
{
	t_lst	*tmp;
	size_t	i;

	i = 0;
	while (i < hash->size)
	{
		if (ft_lstlen(hash->map[i]) > 0)
		{
			tmp = NULL;
			while (hash->map[i])
			{
				ft_strdel(&((t_db*)(hash->map[i]->content))->bin);
				ft_strdel(&((t_db*)(hash->map[i]->content))->path);
				free(hash->map[i]->content);
				tmp = hash->map[i];
				hash->map[i] = hash->map[i]->next;
				free(tmp);
			}
		}
		i++;
	}
	free(hash->map);
	return;
}

void	print_hash_map(t_hash *hash)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;
	int		z;

	i = 0;
	map = hash->map;
	cur_map = NULL;
	while (i < hash->size)
	{
		z = 0;
		cur_map = map[i];
		while (cur_map)
		{
			if (z > 0)
				printf("\t");
			printf("[%zu][%d] BIN|%s| PATH|%s|\n", i, z,
				((t_db*)(cur_map->content))->bin,
				((t_db*)(cur_map->content))->path);
			cur_map = cur_map->next;
			z++;
		}
		i++;
	}
}

void	fill_new_hash_map(t_hash *hash)
{
	t_lst		**new_map;
	t_lst		**map;
	t_lst		*cur_map;
	u_int32_t	value;
	size_t	i;

	i = 0;
	map = hash->map;
	hash->count = 0;
	hash->col = 0;
	new_map = ft_memalloc(sizeof(t_lst*) * (hash->size * 2));
	while (i < hash->size)
	{
		cur_map = map[i];
		while (cur_map)
		{
			hash->count++;
			value = get_hash(((t_db*)(cur_map->content))->bin, (hash->size * 2));
			if (ft_lstlen(new_map[value]) > 0)
				hash->col++;
			ft_lstappend(&new_map[value],
				ft_lstnew(fetch(hash, ((t_db*)(cur_map->content))->bin,
					((t_db*)(cur_map->content))->path), sizeof(t_db)));
			cur_map = cur_map->next;
		}
		i++;
	}
	free_hash_map(hash);
	hash->map = new_map;
	hash->size *= 2;
}

int		main(void)
{
	t_hash	hash;
	size_t	i;

	float float1 = 0;
	float float2 = 0;

	i = 0;
	init_hash_map(&hash);
	hash.map = ft_memalloc(sizeof(t_lst*) * hash.size);
	fill_hash_map(&hash);
	//print_hash_map(&hash);
	float1 = (hash.col * 100) / hash.size;
	float2 = hash.count / hash.size;
	//printf("\nCOLLISION\n\n[%d] %0.2f %c\n\nLOAD FACTOR\n\n%0.2f\n\n", hash.col, float1, '%', float2);


	if (float2 > 0.75)
	{
//		printf("RESZIE NEEDED %d\n", hash.size);
		fill_new_hash_map(&hash);
	}
	float1 = (hash.col * 100) / hash.size;
	float2 = hash.count / hash.size;
//	print_hash_map(&hash);
	//printf("\nCOLLISION\n\n[%d] %0.2f %c\n\nLOAD FACTOR\n\n%0.2f\n\n", hash.col, float1, '%', float2);
	float1 = 0;
	float2 = 0;
	free_hash_map(&hash);
	return (0);
}
