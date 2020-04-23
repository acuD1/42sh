/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:32:08 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:01:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

void	print_usage(const char *name, u_int8_t c, const char *usage)
{
	if (c > 0)
		ft_dprintf(STDERR_FILENO, "42sh: %s: -%c: invalid option\n", name, c);
	ft_dprintf(STDERR_FILENO, "%s: usage: %s\n", name, usage);
}

void	print_and_quit(t_core *shell, const char *message)
{
	ft_dprintf(STDERR_FILENO, "%s", message);
	quit_shell(shell, EXIT_FAILURE, FALSE);
}

void	ft_perror(const char *s, const char *name, int8_t errnum)
{
	static const char	*error[71] = {"Undefined error: 0", 0
		, "No such file or directory", 0, 0, 0, 0, 0, 0, 0, 0, 0
		, "Cannot allocate memory", "Permission denied", 0, 0, 0, 0, 0, 0
		, "Not a directory", "Is a directory", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, "File name too long", 0, 0, 0, 0, 0, 0, 0};

	if (name != NULL)
		ft_dprintf(STDERR_FILENO, "42sh: %s: %s: %s\n", name, s, error[errnum]);
	else
		ft_dprintf(STDERR_FILENO, "42sh: %s: %s\n", s, error[errnum]);
}
