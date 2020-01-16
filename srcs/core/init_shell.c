/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/16 23:54:15 by mpivet-p         ###   ########.fr       */
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
	shell->build = (struct s_build){BUILDR, BUILDV, BUILDP + 1, DATE};
	shell->hash.size = HASH_SIZE;
	shell->terminal = STDIN_FILENO;

	get_core(shell);
	if (set_env(shell, av, env) != SUCCESS)
		quit_shell(shell, EXIT_FAILURE, FALSE);
	if ((shell->is_interactive = isatty(shell->terminal)))
	{
		while (tcgetpgrp(shell->terminal) != (shell->pgid = getpgrp()))
			kill(- shell->pgid, SIGTTIN);
		shell->pgid = getpid();
		if (setpgid(shell->pgid, shell->pgid) < 0)
			print_and_quit(shell, "42sh: Couldn't put the shell in its own process group\n");
		init_signals();
		if (tcsetpgrp(shell->terminal, shell->pgid) != SUCCESS)
			print_and_quit(shell, "42sh: tcsetpgrp error\n");
		if (tcgetattr(shell->terminal, &(shell->old_t)) != SUCCESS)
			print_and_quit(shell, "42sh: tcgetattr error\n");
	}
}
