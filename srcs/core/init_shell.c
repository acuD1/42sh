/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/22 19:25:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

/*
**	Global variable are initialized here. We need to figure it out wich ones
**	need to be shared.
*/

void	init_shell(t_core *shell, char **av, char **env)
{
	/* Initializing values */
	shell->build = (struct s_build){BUILDR, BUILDV, BUILDP + 1, DATE};
	shell->hash.size = HASH_SIZE;
	shell->terminal = STDIN_FILENO;
	

	/* Saving t_core struct to avoid using global variable */
	get_core(shell);
	if (set_env(shell, av, env) != SUCCESS)
		quit_shell(shell, EXIT_FAILURE, FALSE);

	/* TERMINAL INIT */
	if ((shell->is_interactive = isatty(shell->terminal)))
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp(shell->terminal) != (shell->pgid = getpgrp()))
			kill(- shell->pgid, SIGTTIN);

		/* Put ourselves in our own process group.  */
		shell->pgid = getpid();
		if (setpgid(shell->pgid, shell->pgid) < 0)
		{
			dprintf(STDERR_FILENO, "42sh: Couldn't put the shell in its own process group\n");
			quit_shell(shell, EXIT_FAILURE, FALSE); //MUST BE REPLACED WITH QUIT_SHELL
		}
		init_signals();

		/* Grab control of the terminal.  */
		tcsetpgrp(shell->terminal, shell->pgid);

		/* Save default terminal attributes for shell.  */
		tcgetattr(shell->terminal, &(shell->old_t));
	}
}
