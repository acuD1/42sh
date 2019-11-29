/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/29 04:32:16 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

static void	sig_handle(int signum)
{
	t_core	*shell;

	(void)signum;
	shell = get_core(NULL);
	quit_shell(shell, 0);
}

static void	sig_exit(int signum)
{
	t_core	*shell;

	(void)signum;
	shell = get_core(NULL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(shell->old_t));
	//MAKE SURE EVERYTHING IS FREED
	exit(141);
}

static void	sigh_winch(int signum)
{
	t_core	*shell;

	(void)signum;
	shell = get_core(NULL);
	printf("CC\n");
	if (get_size(&(shell->cmd_line)) != SUCCESS || update_termsize(shell))
		quit_shell(shell, 1);
}

void		init_signals(void)
{
	static void (*sighandler[31])(int) = {SIG_DFL, sigint_handler, SIG_DFL /*HUP INT QUIT*/
		, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, NULL, SIG_DFL /*ILL TRAP ABRT EMT FPE (KILL uncatch)BUS*/
		, SIG_DFL, SIG_DFL, sig_exit, SIG_DFL, SIG_DFL, NULL, SIG_DFL/*SEGV SYS PIPE ALRM URG (STOP uncatchable) TSTP*/
		, sig_handle, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL /*CONT CHLD TTIN TTOU IO XCPU XFSZ*/
		, SIG_DFL, SIG_DFL, sigh_winch, NULL, SIG_DFL, SIG_DFL}; /*VTALRM PROF WINCH INFO USR1 USR2*/
	int i;

	i = 1;
	while (i <= SIGUSR2)
	{
		if (sighandler[i - 1] != NULL)
			signal(i, sighandler[i - 1]);
		i++;
	}
}
