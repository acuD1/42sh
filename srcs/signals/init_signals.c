/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/24 20:54:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

void	sigh_hup(int signum)
{
	dprintf(STDERR_FILENO, "SIGNUM CATCHED (Need to kill all child processes)\n");
	exit(signum);
}

void	sigoff(int signum)
{
	dprintf(STDERR_FILENO, "unknown signal %i\n", signum);
	//exit(signum);
}

void	sigh_exit(int signum)
{
	dprintf(STDERR_FILENO, "Free all the memory, restore termios, exit shell, %i\n", signum);
	//exit(signum);
}

void	init_signals(void)
{
	static void (*sighandler[29])(int) = {sigh_hup, sigint_handler, sigoff /*HUP INT QUIT*/
		, sigh_exit, sigh_exit, sigh_exit, sigh_exit, sigh_exit, sigoff /*ILL TRAP ABRT EMT FPE (KILL uncatch)BUS*/
		, sigh_exit, sigh_exit, sigoff, sigoff, sigoff, sigoff, sigoff /*SEGV SYS PIPE ALRM URG (STOP uncatchable) TSTP*/
		, sigh_exit, sigoff, sigoff, sigoff, sigoff, sigh_exit, sigh_exit /*CONT CHLD TTIN TTOU IO XCPU XFSZ*/
		, sigh_exit, sigh_exit, sigoff, sigoff, sigh_exit, sigh_exit}; /*VTALRM PROF WINCH INFO USR1 USR2*/
	int i;

	i = 1;
	while (i <= SIGUSR2)
	{
		signal(i, sighandler[i - 1]);
		i += (i + 1 == SIGKILL || i + 1 == SIGSTOP) ? 2 : 1;
	}
}
