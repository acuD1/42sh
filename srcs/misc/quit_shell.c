/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/05/07 14:32:01 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

void	quit_shell(t_core *shell, int exit_value, int8_t v)
{
	ft_strdel(&shell->term.cpy);
	write_history(shell);
	if (shell->is_interactive)
	{
		reset_config(shell);
		save_history(&shell->term);
		write_history(shell);
	}
	free_shell(shell);
	if (shell->is_interactive && v == TRUE)
		write(STDERR_FILENO, "exit\n", 5);
	exit(exit_value);
}
