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
	static char	*message[32] = {"Done\n", "Hangup\n", "Interrupt\n"
		, "Quit\n", "Illegal instruction\n", "Trace/BPT trap\n"
		, "Abort trap\n", "EMT trap\n", "Floating point exception\n"
		, "Killed\n", "Bus error\n", "Segmentation fault\n"
		, "Bad system call\n", "Broken pipe\n", "Alarm clock\n"
		, "Terminated\n", NULL, "Stopped (signal)\n"
		, "Stopped\n", NULL, NULL, "Stopped (tty input)\n"
		, "Stopped (tty output)\n", NULL, "Cputime limit exceeded\n"
		, "Filesize limit exceeded\n", "Virtual timer expired\n"
		, "Profiling timer expired\n", NULL, "Information request\n"
		, "User defined signal 1\n", "User defined signal 2\n"};

	sig = get_signal(sig);
	if (sig >= 0 && sig <= 31)
		return (message[sig]);
	return (NULL);
}

void	status_handler(t_core *shell, t_process *process)
{
	int		status;
	char	*msg;

	status = 0;
	msg = NULL;
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
