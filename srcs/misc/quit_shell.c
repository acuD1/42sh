/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/17 23:49:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v)
{
	if (shell->mode & OPT_MODE)
	{
		free_db(shell->env);
//		longjmp(g_exit_leaks, 42); /* TEMPORARY */
		exit(exit_value);
	}
	if (shell->mode & I_MODE && shell->opt == 0)
		reset_config(shell);
	free_shell(shell);
	if (v == TRUE && shell->mode & I_MODE)
		write(STDERR_FILENO, "exit\n", 5);
//	longjmp(g_exit_leaks, 42); /* TEMPORARY */
	exit(exit_value);
}
