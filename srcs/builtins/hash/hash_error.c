/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:21:14 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/28 17:40:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

void	hash_error(t_hash *hash)
{
	ft_perror("hash", NULL, ENOMEM);
	free_hash_map(hash);
}
