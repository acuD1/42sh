/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

char				*simple_format(char *str, t_core *shell)
{
	t_db	*db_tmp;

	db_tmp = NULL;
	if (!(ft_strchr(str, '$') && str[0] != '$')
			&& (db_tmp = search_db(shell->env, str)))
	{
		ft_strdel(&str);
		return (ft_strdup(db_tmp->value));
	}
	shell->status = 1;
	ft_strdel(&str);
	return (NULL);
}

char				*format_supplementaires(char *str, t_core *shell)
{
	size_t	i;

	i = 0;
	if (str[0] == ':' || str[0] == '%')
	{
		ft_strdel(&str);
		return (NULL);
	}
	if (str[i] == '#')
		return (length_format(str, shell));
	while (str[i])
	{
		if (str[i] == ':')
			return (moar_format_plz(str, shell));
		else if (str[i] == '%')
			return (suffix_format(str, shell));
		else if (str[i] == '#')
			return (prefix_format(str, shell));
		i++;
	}
	return (simple_format(str, shell));
}

static u_int32_t	check_param_exp(char *str, size_t *i, t_core *shell)
{
	if ((str[*i] == '\\' && str[*i + 1] && str[*i + 1] != '\n')
		|| (str[*i] == '\n'))
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		shell->status = 1;
		shell->subst_error = 1;
		return (0);
	}
	return (1);
}

char				*get_brace_param(char *str, t_core *shell)
{
	size_t		i;
	u_int32_t	count;
	char		*tmp;

	i = 1;
	count = 0;
	tmp = NULL;
	while (str[i++])
	{
		if (!check_param_exp(str, &i, shell))
			break ;
		if (!check_brackets_inbracket(&count, str[i]))
			break ;
	}
	if (!(tmp = ft_strsub(str, 2, i - 2)))
		return (NULL);
	return (format_supplementaires(tmp, shell));
}

char				*exp_param(const char *data, t_core *shell)
{
	if (data[0] == '$' && data[1] == '{')
		return (get_brace_param((char*)data, shell));
	if (data[0] == '$' && data[1])
		return (simple_format(ft_strsub(data, 1, ft_strlen(data) - 1), shell));
	return (NULL);
}
