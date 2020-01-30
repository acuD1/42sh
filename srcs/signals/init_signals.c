/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/30 19:18:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

static void	sig_handler(int signum)
{
	t_core	*shell;
	pid_t	pid;

	shell = get_core(NULL);
	if (signum == SIGTSTP)
		return ;
	reset_config(shell);
	pid = getpid();
	signal(signum, SIG_DFL);
	kill(pid, signum);
}

static void	sig_exit(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	quit_shell(shell, 141, (signum == SIGPIPE) ? FALSE : TRUE, I_MODE);
}

static void	sigh_winch(int signum)
{
	t_core	*shell;

	(void)signum;
	fflush(stdout);
	shell = get_core(NULL);
	if (get_size(&(shell->term)) != SUCCESS || update_termsize(shell))
		quit_shell(shell, EXIT_SUCCESS, FALSE, I_MODE);
}

/*
**	HUP INT
**	QUIT ILL TRAP ABRT EMT
**	FPE KILL(NULL)BUS SEGV SYS PIPE
**	ALRM TERM URG STOP(NL) TSTP CONT
**	CHLD TTIN TTOU IO XCPU XFSZ
**	VTALRM PROF WINCH INFO USR1
**	USR2
*/

void		init_signals(void)
{
	static void	(*sighandler[31])(int) = {sig_handler, sigint_handler
		, sig_handler, sig_handler, sig_handler, sig_handler, sig_handler
		, sig_handler, NULL, sig_handler, sig_handler, sig_handler, sig_exit
		, sig_handler, sig_handler, sig_handler, NULL, SIG_IGN, sig_exit
		, SIG_DFL, SIG_IGN, SIG_IGN, SIG_DFL, sig_handler, sig_handler
		, sig_handler, sig_handler, sigh_winch, NULL, sig_handler
		, sig_handler};
	int			i;

	i = 1;
	while (i <= SIGUSR2)
	{
		if (sighandler[i - 1] != NULL)
			if (signal(i, sighandler[i - 1]) != 0)
				dprintf(STDERR_FILENO, "%i\n", i);
		i++;
	}
}
