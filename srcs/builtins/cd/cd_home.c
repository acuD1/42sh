/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:40:17 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/10 16:40:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	cd_home(t_core *shell)
{
	char	pwd[MAX_PATH + 1];
	t_db	*var;

	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) == NULL && shell->cd.pwd_error == TRUE)
		ft_dprintf(STDERR_FILENO, "%s %s No such file or directory\n",
			CHDIR_ERR, GETCWD_ERR);
	if ((var = search_db(shell->env, "HOME")) == NULL)
	{
		write(STDERR_FILENO, "42sh: cd: HOME not set\n", 23);
		return (1);
	}
	shell->cd.pwd_error = FALSE;
	if (chdir(var->value) != SUCCESS)
		ft_perror(var->value, "cd", cd_check_path(var->value));
	return (update_pwds(shell, pwd, NULL));
}
