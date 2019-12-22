/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/22 16:31:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t verbose)
{
	(void)exit_value;
	reset_config(shell);
	//MAKE SUR EVERYTHING IS FREED
	free_prompt(shell);
	free_env(shell->env);
	free_hash_map(&shell->hash);
	free_history(&shell->term);
	if (verbose != 0)
		write(STDERR_FILENO, "exit\n", 5);
	longjmp(exit_leaks, 42);
	//exit(exit_value);
}
