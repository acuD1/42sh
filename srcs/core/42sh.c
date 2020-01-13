/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/13 15:21:28 by arsciand         ###   ########.fr       */
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
	/*
	// Need "-c implementation and a while to read everything"
	//char BUFF[16];
	if (isatty(STDIN_FILENO) == TRUE)
	{
		if (get_size(&(shell.cmd_line)) != SUCCESS)
			return (EXIT_FAILURE);
		load_prompt(&shell);
	}
	else
	{
		while (ft_getnextline(STDIN_FILENO, &(shell.cmd_line.buffer)))
			load_noi_mode(&shell);
		ft_strdel(&(shell.cmd_line.buffer));
	}*/
	if (setjmp(g_exit_leaks))
		dprintf(STDOUT_FILENO, "Exited with free handling ..\n");
	else
	{
		dprintf(STDERR_FILENO, "Entering 42sh with setjmp activated !!!\n");
		if (isatty(STDIN_FILENO) == TRUE)
		{
			if (get_size(&shell.term) != SUCCESS)
				quit_shell(&shell, EXIT_FAILURE, FALSE, I_MODE);
			shell.mode |= I_MODE;
		}
		else
			shell.mode |= NOI_MODE;
		shell_loader(&shell);
	}
	dprintf(STDERR_FILENO, "?\n");
	free_shell(&shell);
	return (EXIT_SUCCESS);
}
