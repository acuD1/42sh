/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:31:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/08 18:10:11 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	status_handler(t_core *shell, int status)
{
	static char *message[31] = {"Hangup: 1\n", NULL, "Quit: 3\n"
		, "Illegal instruction: 4\n", "Trace/BPT trap: 5\n", "Abort trap:6\n"
		,"EMT trap: 7\n", "Floating point exception: 8\n", "Killed: 9\n"
		, "Bus error: 10\n", "Segmentation fault: 11\n"
		, "Bad system call: 12\n", NULL, "Alarm clock: 14\n"
		, "Terminated: 15\n", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
		, "Cputime limit exceeded: 24\n", "Filesize limit exceeded: 25\n"
		, "Virtual timer expired: 26\n", "Profiling timer expired: 27\n", NULL
		, NULL, "User defined signal 1: 30\n", "User defined signal 2: 31\n"};

	if (WIFSIGNALED(status))
	{
		if (message[status - 1] != NULL)
			write(STDERR_FILENO, message[status - 1], ft_strlen(message[status - 1]));
		shell->status = status + 128;
	}
	else
		shell->status = WEXITSTATUS(status);
}
