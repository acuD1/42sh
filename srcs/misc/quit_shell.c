/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/26 12:33:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v)
{
	//longjmp(g_exit_leaks, 42); /* TEMPORARY */
	if (shell->is_interactive)
		reset_config(shell);
	free_shell(shell);
	if (shell->is_interactive && v == TRUE)
		write(STDERR_FILENO, "exit\n", 5);
	longjmp(g_exit_leaks, 42); /* TEMPORARY */
	exit(exit_value);
}
