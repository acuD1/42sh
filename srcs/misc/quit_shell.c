/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/26 17:26:49 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v)
{
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
