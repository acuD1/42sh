/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:31:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/12 17:24:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

char	*signal_msg(int sig)
{
	static char	*message[32] = {"Done\n", "Hangup: 1\n", "Interrupt: 2\n"
		, "Quit: 3\n", "Illegal instruction: 4\n", "Trace/BPT trap: 5\n"
		, "Abort trap: 6\n", "EMT trap: 7\n", "Floating point exception: 8\n"
		, "Killed: 9\n", "Bus error: 10\n", "Segmentation fault: 11\n"
		, "Bad system call: 12\n", "Broken pipe: 13\n", "Alarm clock: 14\n"
		, "Terminated: 15\n", NULL, "Suspended (signal): 17\n"
		, "Suspended: 18\n", NULL, NULL, "Stopped (tty input): 21\n"
		, "Stopped(SIGTTOU): 22\n", NULL, "Cputime limit exceeded: 24\n"
		, "Filesize limit exceeded: 25\n", "Virtual timer expired: 26\n"
		, "Profiling timer expired: 27\n", NULL, "Information request: 29\n"
		, "User defined signal 1: 30\n", "User defined signal 2: 31\n"};

	sig = get_signal(sig);
	if (sig >= 0 && sig <= 31)
		return (message[sig]);
	return (NULL);
}

void	status_handler(t_core *shell, t_process *process)
{
	int		status;
	char	*msg;

	if (WIFSIGNALED(process->status))
	{
		status = WTERMSIG(process->status);
		msg = signal_msg(status);
		if (msg != NULL && status != 0 && status != 13 && status != 2)
			write(2, msg, ft_strlen(msg));
	}
	else if (WIFSTOPPED(process->status))
	{
		status = WSTOPSIG(process->status);
	}
	else if (process->type == P_PIPE)
		return ;
	else
	{
		shell->status = WEXITSTATUS(process->status);
		return ;
	}
	shell->status = status + 128;
}
