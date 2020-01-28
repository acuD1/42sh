/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:13 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/28 20:22:36 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*exp_tilde(char *data, t_core *shell)
{
	t_db	*db_tmp;
	char	*path[] = {"HOME", "OLDPWD", "PWD"};
	int		i;

	i = 0;
	db_tmp = NULL;
	if (!data && !data[0])
		return (NULL);
	if (data[0] == '~' && data[1] && data[1] == '+')
		i = 2;
	else if (data[0] == '~' && data[1] && data[1] == '-')
		i = 1;
	else if (data[0] == '~')
		i = 0;
	if ((db_tmp = search_db(shell->env, path[i])))
		return (ft_strdup(db_tmp->value));
	return (NULL);
}
