/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/08 22:02:24 by mpivet-p         ###   ########.fr       */
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
	{
		printf("CC -> sig_handler\n");
		return ;
	}
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

void		init_signals(void)
{
	static void (*sighandler[31])(int) = {sig_handler, sigint_handler /* HUP INT */
		, sig_handler, sig_handler, sig_handler, sig_handler, sig_handler /* QUIT ILL TRAP ABRT EMT */
		, sig_handler, NULL, sig_handler, sig_handler, sig_handler, sig_exit /*FPE KILL(NULL)BUS SEGV SYS PIPE*/
		, sig_handler, sig_handler, sig_handler, NULL, SIG_IGN, sig_exit/*ALRM TERM URG STOP(NL) TSTP CONT*/
		, SIG_DFL, SIG_IGN, SIG_IGN, SIG_DFL, sig_handler, sig_handler /*CHLD TTIN TTOU IO XCPU XFSZ*/
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
