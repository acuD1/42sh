/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:51:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/07 21:05:56 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

int8_t	builtin_pwd(t_core *shell, t_process *process)
{
	char	pwd[MAX_PATH + 1];

	(void)shell;
	(void)process;
	ft_bzero(pwd, MAX_PATH + 1);
	if (getcwd(pwd, MAX_PATH) == NULL)
	{
		ft_perror(pwd, "pwd", ENOENT);
		return (1);
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
