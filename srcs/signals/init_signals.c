/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/01 11:32:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

static void	sig_handler(int signum)
{
	static char *message[31] = {"Hangup", NULL, "Quit", "Illegal instruction"
		, "Trace/BPT trap", "Abort trap\n", "EMT trap"
		, "Floating point exception", "Killed", "Bus error"
		, "Segmentation fault", "Bad system call", NULL, "Alarm clock"
		, "Terminated", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
		, "Cputime limit exceeded", "Filesize limit exceeded"
		, "Virtual timer expired", "Profiling timer expired", NULL, NULL
		, "User defined signal 1", "User defined signal 2"};
	t_core	*shell;

	shell = get_core(NULL);
	if (signum == SIGHUP && shell->running_process)
		kill_processes(SIGHUP, shell);
	if (message[signum - 1] != NULL)
		dprintf(STDERR_FILENO, "%s: %i (42sh)\n", message[signum - 1], signum);
	quit_shell(shell, 0, 0);
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

void		init_signals(void)
{
	static void (*sighandler[31])(int) = {sig_handler, sigint_handler /* HUP INT */
		, sig_handler, sig_handler, sig_handler, sig_handler, sig_handler /* QUIT ILL TRAP ABRT EMT */
		, sig_handler, NULL, sig_handler, sig_handler, sig_handler, sig_exit /*FPE KILL(NULL)BUS SEGV SYS PIPE*/
		, sig_handler, sig_handler, sig_handler, NULL, sig_handler, sig_exit/*ALRM TERM URG STOP(NL) TSTP CONT*/
		, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, sig_handler, sig_handler /*CHLD TTIN TTOU IO XCPU XFSZ*/
		, sig_handler, sig_handler, sigh_winch, NULL, sig_handler /*VTALRM PROF WINCH INFO USR1 */
		, sig_handler}; /* USR2*/
	int i;

	i = 1;
	while (i <= SIGUSR2)
	{
		if (sighandler[i - 1] != NULL)
			if (signal(i, sighandler[i - 1]) != 0)
				dprintf(STDERR_FILENO, "%i\n", i);
		i++;
	}
}
