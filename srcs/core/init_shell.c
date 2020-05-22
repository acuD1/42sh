/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:44:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	init_shell_pgid(t_core *shell)
{
	while (tcgetpgrp(shell->terminal) != (shell->pgid = getpgrp()))
		kill(-shell->pgid, SIGTTIN);
	shell->pgid = getpid();
	if (setpgid(shell->pgid, shell->pgid) < 0)
		print_and_quit(shell,
			"42sh: Couldn't put the shell in its own process group\n");
	init_signals();
	if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
		print_and_quit(shell, "42sh: tcsetpgrp error\n");
}

int8_t		init_shell(t_core *shell, char **av, char **environ)
{
	shell->hash.size = HASH_SIZE;
	shell->terminal = STDIN_FILENO;
	shell->ctrl_c = 0;
	get_core(shell);
	if (set_env(shell, av, environ) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "42sh: Cannot allocate memory\n");
		return (EXIT_FAILURE);
	}
	if (isatty(shell->terminal) == TRUE)
	{
		shell->is_interactive = TRUE;
		init_config(shell);
		init_shell_pgid(shell);
	}
	else
		shell->is_interactive = FALSE;
	return (SUCCESS);
}
