/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:32:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/15 20:38:59 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_usage(char *name, int c, char *usage)
{
	if (c > 0)
		dprintf(STDERR_FILENO, "%s: -%c: invalid option\n", name, c);
	dprintf(STDERR_FILENO, "%s: usage: %s\n", name, usage);
}

void	print_and_quit(t_core *shell, char *message)
{
	dprintf(STDERR_FILENO, "%s", message);
	quit_shell(shell, EXIT_FAILURE, FALSE);
}

void	ft_perror(const char *s, const char *name, const int errnum)
{
	static char	*error[] = {
		"Undefined error: 0", 0, "No such file or directory", 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, "Permission denied", 0, 0, 0, 0, 0, 0, "Not a directory"
		, "Is a directory", 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, "File name too long", 0, 0, 0, 0, 0, 0, 0
	};

	if (name != NULL)
		dprintf(STDERR_FILENO, "42sh: %s: %s: %s\n", name, s, error[errnum]);
	else
		dprintf(STDERR_FILENO, "42sh: %s: %s\n", s, error[errnum]);
}
