/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:57:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 21:11:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	check_invalid_identifiers(const char *arg, const char *exceptions)
{
	size_t	i;

	i = 0;
	if (!(arg[0]))
		return (FAILURE);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) != SUCCESS
			&& ft_strchr(exceptions, arg[i]) == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
