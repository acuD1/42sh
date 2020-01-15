/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/15 09:30:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	ft_bzero(&shell, sizeof(t_core));
	init_shell(&shell);
	if (get_opt(ac, av, &shell) != SUCCESS)
		return (EXIT_FAILURE);
	if (set_env(&shell, av, environ) != SUCCESS)
		return (EXIT_FAILURE);
	print_opt(&shell);
	get_core(&shell);
	init_signals();
	if (setjmp(g_exit_leaks))
	{
		dprintf(STDOUT_FILENO, "Exited with free handling ..\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		dprintf(STDERR_FILENO, "Entering 42sh with setjmp activated !!!\n");
		if (isatty(STDIN_FILENO) == TRUE)
		{
			if (get_size(&shell.term) != SUCCESS)
				quit_shell(&shell, EXIT_FAILURE, FALSE, I_MODE);
			load_i_mode(&shell);
		}
		else
			load_noi_mode(&shell);
	}
	free_shell(&shell);
	dprintf(STDERR_FILENO, "%sEXIT_SUCCESS%s\n", C_G, C_X);
	return (EXIT_SUCCESS);
}
