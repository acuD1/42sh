/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/13 15:08:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v, u_int8_t mode)
{
	if (mode & I_MODE)
		reset_config(shell);
	free_shell(shell);
	if (v == TRUE)
		write(STDERR_FILENO, "exit\n", 5);
	longjmp(g_exit_leaks, 42);
	exit(exit_value);
}
