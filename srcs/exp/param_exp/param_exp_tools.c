/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:22 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

char		*one_moar_error(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", tablo[0]);
	ft_strdel(&data);
	ft_strdel(&tablo[0]);
	ft_strdel(&tablo[1]);
	shell->subst_error = 1;
	return (NULL);
}

char		*error_brace_param(char *str, t_core *shell, char *tmp)
{
	ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
	shell->subst_error = 1;
	ft_strdel(&tmp);
	return (NULL);
}

char		*check_env_key(char *key, t_core *shell)
{
	t_db	*db;

	db = search_db(shell->env, key);
	if (db)
		return (db->value);
	return (NULL);
}

u_int32_t	check_format_bracket(char c)
{
	if (c == '?' || c == '=' || c == '-' || c == '+')
		return (1);
	return (0);
}

void		fill_thereste(char *str, char *tmp, int *index, int *i)
{
	while (str[*i])
	{
		if (!str[*i + 1])
			break ;
		tmp[*index] = str[*i];
		*index += 1;
		*i += 1;
	}
}
