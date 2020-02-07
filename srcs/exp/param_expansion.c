/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/07 05:32:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*get_brace_param(const char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '}')
			break ;
	}
	if (!(tmp = ft_strsub(str, 2, i - 2)))
		return (NULL);
	return (tmp);
}

char		*exp_param(const char *data, t_core *shell)
{
	t_db	*db_tmp;
	char	*tmp;
	int		i;

	i = ft_strlen(data);
	tmp = NULL;
	db_tmp = NULL;
	if (data[0] == '$' && data[1] == '{')
		tmp = get_brace_param(data);
	else if (data[0] == '$')
		tmp = ft_strsub(data, 1, i - 1);
	if ((db_tmp = search_db(shell->env, tmp)))
	{
		free(tmp);
		return (ft_strdup(db_tmp->value));
	}
	free(tmp);
	return (NULL);
}
