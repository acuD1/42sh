/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 22:26:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:31:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>

static int	signal_comp(int signum)
{
	static int	sig_comp[32] = {0, SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP
								, SIGABRT, SIGEMT, SIGFPE, SIGKILL, SIGBUS
								, SIGSEGV, SIGSYS, SIGPIPE, SIGALRM, SIGTERM
								, SIGURG, SIGSTOP, SIGTSTP, SIGCONT, SIGCHLD
								, SIGTTIN, SIGTTOU, SIGIO, SIGXCPU, SIGXFSZ
								, SIGVTALRM, SIGPROF, SIGWINCH, SIGINFO
								, SIGUSR1, SIGUSR1};
	int			i;

	i = 0;
	while (i++ < 32)
		if (signum == sig_comp[i])
			return (i);
	return (0);
}

int			get_signal(int status)
{
	if (WIFSTOPPED(status))
	{
		return (signal_comp(WSTOPSIG(status)));
	}
	else if (WIFSIGNALED(status))
	{
		return (signal_comp(WTERMSIG(status)));
	}
	return (0);
}
