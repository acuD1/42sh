/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_cmds_math_exp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:13 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 06:26:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*no_exp(const char *data, t_core *shell)
{
	(void)shell;
	return (ft_strdup(data));
}

char	*exp_math(const char *data, t_core *shell)
{
	(void)shell;
	return (ft_strdup(data));
}

char	*exp_tilde(const char *data, t_core *shell)
{
	t_db	*db_tmp;
	char	*path[3];
	int		i;

	i = 0;
	db_tmp = NULL;
	path[0] = "HOME";
	path[1] = "OLDPWD";
	path[2] = "PWD";
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

char	*exp_cmd_subs(const char *data, t_core *shell)
{
	(void)shell;
	return (ft_strdup(data));
}

int		quotes_condition(char c, enum e_estate state)
{
	if ((c == '\"' && state == E_QUOTE) || (c == '\'' && state == E_DBQUOTE))
		return (0);
	return (1);
}
