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

/*
*** CE FICHIER N"EST NI NORME NI LEAK_FREE NI FINIT
*/

char			*simple_format(char *str, t_core *shell)
{
	t_db		*db_tmp;
	
	db_tmp = NULL;
	if ((db_tmp = search_db(shell->env, str)))
	{
		ft_strdel(&str);
		return (ft_strdup(db_tmp->value));
	}
	return (NULL);
}

char			*format_supplementaires(char *str, t_core *shell)
{
	int			i;

	i = 0;
	if (str[0] == ':' || str[0] == '%' || str[0] == '$')
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : mauvaise substitution\n", str);
		return (NULL);
	}
	if(str[i] == '#')
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

static char	*get_brace_param(const char *str, t_core *shell)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '}')
			break ;
	}
	if (!(tmp = ft_strsub(str, 2, i - 2)))
		return (NULL);
	return (format_supplementaires(tmp, shell));
}

char		*exp_param(const char *data, t_core *shell)
{
	char		*tmp;

	tmp = NULL;
	if (data[0] == '$' && data[1] == '{')
		return (tmp = get_brace_param(data, shell));
	else if (data[0] == '$')
	{
		tmp = ft_strsub(data, 1, ft_strlen(data) - 1);
		return (simple_format(tmp, shell));
	}
	return (NULL);
}
