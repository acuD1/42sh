/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:57:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 06:06:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_invalid_identifiers(const char *arg, const char *exceptions)
{
	int		i;

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
