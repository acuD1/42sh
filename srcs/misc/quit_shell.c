/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/25 13:49:58 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v, u_int8_t mode)
{
	if (mode & OPT_MODE)
	{
		free_env(shell->env);
		longjmp(g_exit_leaks, 42); /* TEMPORARY */
		exit(exit_value);
	}
	if (mode & I_MODE && shell->opt == 0)
		reset_config(shell);
	free_shell(shell);
	if (v == TRUE && shell->opt == 0)
		write(STDERR_FILENO, "exit\n", 5);
	longjmp(g_exit_leaks, 42); /* TEMPORARY */
	exit(exit_value);
}
