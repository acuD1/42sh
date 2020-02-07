/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/06 21:51:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

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
	if (tcgetattr(shell->terminal, &(shell->old_t)) != SUCCESS)
		print_and_quit(shell, "42sh: tcgetattr error\n");
}

int8_t		init_shell(t_core *shell, char **av, char **environ)
{
	shell->build = (struct s_build){DATE, BUILDP + 1, BUILDR, BUILDV};
	shell->hash.size = HASH_SIZE;
	shell->terminal = STDIN_FILENO;
	get_core(shell);
	if (set_env(shell, av, environ) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: Cannot allocate memory\n");
		return (EXIT_FAILURE);
	}
	if (isatty(shell->terminal) == TRUE)
	{
		shell->mode |= I_MODE;
		init_shell_pgid(shell);
	}
	else
		shell->mode |= NOI_MODE;
	return (SUCCESS);
}
