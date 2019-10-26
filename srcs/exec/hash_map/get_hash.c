/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:01:50 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/02 15:02:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
