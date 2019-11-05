/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:39:28 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/05 02:03:01 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	exec_handler prints errors occured in exec_process fonctions
**	TO DO :
**	- set env builtin
**	- set expansion variables
*/

static int8_t	exec_handler_bin_error(t_core *shell)
{
	//struct stat stat;

	/*
	**	NOT SUPPORTED YET (exp not set)
	**	Check if tokens[0] is a directory only if
	**	tokens[0] cames from an expansion variable

	if (lstat(shell->tokens[0], &stat) == 0
		&& S_ISDIR(stat.st_mode) && shell->exp == 1)
	{
		dprintf(STDERR_FILENO, "42sh: %s: is a directory\n",
			shell->tokens[0]);
	}

	** NO SUPPORTED YET (env builtin not set)
	else if (shell->env_mode)
		dprintf(STDERR_FILENO, "env: %s: No such file or directory\n",
			shell->tokens[0]);
	else
	*/

	/* If not a directory then the binary is not found at all */
	dprintf(STDERR_FILENO, "42sh: %s: command not found\n",
		shell->tokens[0]);
}

static int8_t	exec_handler_perm_error(t_core *shell)
{
	/* Check if file exist, if not permission denied*/
	if (access(shell->tokens[0], F_OK) == -1)
		dprintf(STDERR_FILENO,
			"42sh: %s: No such file or directory\n", shell->tokens[0]);	/* /!\ */
	else
		dprintf(STDERR_FILENO, "42sh: %s: Permission denied\n",
			shell->tokens[0]);	/* /!\ */
	return (FAILURE);
}

int8_t	exec_handler(t_core *shell, u_int8_t handler)
{
	if (handler & BIN_ERROR)
		return (exec_handler_bin_error(shell));
	if (handler & PERM_ERROR)
		return (exec_handler_perm_error(shell));
	if (handler & FORK_ERROR)
		dprintf(STDERR_FILENO, "%sFork failed !\n%s", C_R, C_X);	/* /!\ */
	return (FAILURE);
}
