/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:57:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/02 02:52:28 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_invalid_identifiers(char *arg, char *exceptions)
{
	int	i;

	i = 0;
	if (!(arg[0]))
		return (FAILURE);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) != SUCCESS && ft_strchr(exceptions, arg[i]) == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
