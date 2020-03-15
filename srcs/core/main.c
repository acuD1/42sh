/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/02 19:37:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	ft_bzero(&shell, sizeof(t_core));
	get_opt(ac, av, &shell);
	if (read(STDIN_FILENO, NULL, 0) < 0
		|| init_shell(&shell, av, environ) != SUCCESS)
		return (0);
	if (shell.is_interactive)
		load_i_mode(&shell);
	else
		load_noi_mode(&shell);
	free_shell(&shell);
	return (shell.status);
}
