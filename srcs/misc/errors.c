/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 01:28:05 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/01 14:49:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_usage(char *name, int c, char *usage)
{
	if (c > 0)
		dprintf(STDERR_FILENO, "42sh: %s: -%c: invalid option\n", name, c);
	dprintf(STDERR_FILENO, "%s: usage: %s\n", name, usage);
}

void	ft_perror(const char *s, const int errnum)
{
	static char	*error[] = {0, 0, "No such file or directory", 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, "Permission denied", 0, 0, 0, 0, 0, 0, "Not a directory"
		, "Is a directory", 0, 0, 0, 0, 0, 0, 0, 0, 0 // 30
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // 40
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // 50
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // 60
		, 0, 0, "File name too long", 0, 0, 0, 0, 0, 0, 0 // 70
	};
	dprintf(STDERR_FILENO, "42sh: %s: %s\n", s, error[errnum]);
}
