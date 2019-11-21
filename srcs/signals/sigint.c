/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/21 22:47:19 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

void	sigint_handler(int sig_num)
{
	t_core	*shell;

	(void)sig_num;
	shell = get_core(NULL);
	if (shell->last_process != NULL)
	{
		kill(shell->last_process->pid, SIGINT);
		write(1, "\n", 1);
	}
}
