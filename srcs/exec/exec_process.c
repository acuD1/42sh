/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:14:57 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/30 10:15:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	exec_process takes for parameter t_lst *env for now because we can set
**	a temporary environnement if we use the env builtin.
*/

void		exec_process(t_core *shell, t_lst *env)
{
	char	**envp; // envp formated for excve
	pid_t	child;	// child pid after fork
	int		status;	// status for waitpid

	envp = NULL;

	/* get_bin check if is a local binary or find the binary in PATH or hash table*/
	shell->bin = get_bin(shell, env);

	/*
	**	Several check are listed here, such as :
	**	- if the binary exist in PATH from get_bin
	**	- if the binary have exec permission
	**	- if the binary can be forked
	*/
	if (shell->bin == NULL)
		return (exec_handler(shell, BIN_ERROR));
	if (access(shell->bin, X_OK) == FAILURE)
		return (exec_handler(shell, PERM_ERROR));
	if ((child = fork()) < 0)
		return (exec_handler(shell, FORK_ERROR));

	/*
	**	set_envp format a table of environement for execve.
	**	like : PATH=/usr/bin
	*/
	envp = set_envp(shell);

	/* binary is executed here by execve */
	if (child == 0 && execve(shell->bin, shell->tokens, envp) < 0)
	{
		ft_tabdel(&envp);
		return (exec_handler(shell, EXEC_ERROR));
	}

	/* We're checking the waitpid status here */
	else
	{
		waitpid(child, &status, WCONTINUED);
		/* waitpid_status_handler(shell); Segv catcher not set yet */
	}
	ft_tabdel(&envp);
}
