/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 01:28:05 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 01:32:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_usage(char *name, int c, char *usage)
{
	if (c > 0)
		dprintf(STDERR_FILENO, "pistash: %s: -%c: invalid option\n", name, c);
	dprintf(STDERR_FILENO, "%s: usage: %s", name, usage);
}
