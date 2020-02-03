/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/03 16:45:48 by mpivet-p         ###   ########.fr       */
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
	reset_config(shell, &(shell->cmd_line));
	pid = getpid();
	signal(signum, SIG_DFL);
	kill(pid, signum);
}

static void	sig_exit(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	quit_shell(shell, 141, (signum == SIGPIPE) ? 0 : 1);
}

static void	sigh_winch(int signum)
{
	t_core	*shell;

	(void)signum;
	fflush(stdout);
	shell = get_core(NULL);
	if (get_size(&(shell->cmd_line)) != SUCCESS || update_termsize(shell))
		quit_shell(shell, 1, 1);
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

	signal(SIGHUP, sig_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGILL, sig_handler);
	signal(SIGTRAP, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGEMT, sig_handler);
	signal(SIGFPE, sig_handler);
//kill == null
	signal(SIGBUS, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGSYS, sig_handler);
	signal(SIGPIPE, sig_exit);
	signal(SIGALRM, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGURG, sig_handler);
//STOP = NULL
	signal(SIGTSTP, sig_handler);
	signal(SIGCONT, sig_exit);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGIO, SIG_DFL);
	signal(SIGXCPU, sig_handler);
	signal(SIGXFSZ, sig_handler);
	signal(SIGVTALRM, sig_handler);
	signal(SIGPROF, sig_handler);
	signal(SIGWINCH, sigh_winch);
// INFO null
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
}
/*
void		init_signals(void)
{
	static void	(*sighandler[32])(int) = {NULL, sig_handler, sigint_handler
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
		if (sighandler[i] != NULL)
			if (signal(i, sighandler[i - 1]) != 0)
				dprintf(STDERR_FILENO, "%i\n", i);
		i++;
	}
}*/
