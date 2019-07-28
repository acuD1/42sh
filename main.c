/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 11:18:53 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/28 18:59:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "shared_libft.h"
#include "define.h"
#include <limits.h>
#define L 620000 //75% load factor

u_int32_t	get_hash(char *line)
{
	u_int32_t hash = 0;
	size_t i = 0;
	while (i < ft_strlen(line))
	{
		hash = ((hash << 8) + line[i]) % L;
		i++;
	}
	return (hash);
}

int8_t	linear_probing(char **tab, char *line, u_int32_t hash)
{
	while (hash < L)
	{
		if (tab[hash] == NULL)
		{
			tab[hash] = ft_strdup(line);
			return (SUCCESS);
		}
		hash++;
	}
	return (FAILURE);
}

u_int32_t	check_tab(char **tab)
{
	u_int32_t cell_filled = 0;
	size_t	len = L;

	while (len--)
	{
		if (tab[len])
			cell_filled++;
	}
	return (cell_filled);
}

int	main(void)
{
	char		*line;
	char		**tab = NULL;
	u_int32_t	hash;
	int			fd;
	size_t		i;
	size_t		c = 0;

	i = 0;
	hash = 0;
	line = NULL;
	//ft_bzero(tab, sizeof(tab) * L);
	fd = open("words.txt.bak", O_RDONLY);
	tab = ft_memalloc(sizeof(tab) * (L + 1));
	while (ft_getnextline(fd, &line))
	{
		hash = get_hash(line);
		if (tab[hash] && linear_probing(tab, line, hash) != SUCCESS)
			c++;
		else
			tab[hash] = ft_strdup(line);
//		printf("word = |%s| hash = |%u|\n", line, hash);
		free(line);
	}
	tab[L] = NULL;
	while (i < L)
	{
		if (tab[i])
			printf("tab[%zu] = |%s|\n", i, tab[i]);
		i++;
	}
	printf("tablen = |%d|\ncollision = |%zu| %0.2f%c\n\n", check_tab(tab), c, (float)(c * 100) / L, '%');
	close(fd);
}
