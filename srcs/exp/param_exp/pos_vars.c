/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:16:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/05/19 16:26:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_pos_vars(char c)
{
	if (c == '#' || c == '@' || c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}

static char	*concat_pos_vars(t_core *shell)
{
	t_lst	*tmp;
	char	*res;

	res = NULL;
	tmp = shell->pos_vars;
	while (tmp)
	{
		if (!res)
			res = ft_strdup(((t_db*)tmp->content)->value);
		else
		{
			res = ft_strjoinf(res, " ", 1);
			res = ft_strjoinf(res, ((t_db*)tmp->content)->value, 1);
		}
		tmp = tmp->next;
	}
	return (res);
}

char		*pos_vars_format(char *str, t_core *shell)
{
	t_db	*db_tmp;
	char	*res;

	db_tmp = NULL;
	res = NULL;
	if (!shell->pos_vars)
	{
		ft_strdel(&str);
		return (NULL);
	}
	if (str[0] == '#')
		res = ft_itoa((int32_t)ft_lstlen(shell->pos_vars));
	else if (str[0] == '@' || str[0] == '*')
		res = concat_pos_vars(shell);
	else if (!(ft_strchr(str, '$') && str[0] != '$')
			&& (db_tmp = search_db(shell->pos_vars, str)))
		res = ft_strdup(db_tmp->value);
	ft_strdel(&str);
	return (res);
}
