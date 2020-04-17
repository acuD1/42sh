/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:03:59 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/17 11:46:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		insert_dollar(char **insert, const char *to_find, char *key)
{
	if (!ft_strcmp(to_find, "${"))
	{
		*insert = ft_strjoin("${", key);
		*insert = ft_strjoinf(*insert, "}", 1);
	}
	else if (to_find[0] == '$')
		*insert = ft_strjoin("$", key);
}

static u_int8_t	var_is_matching(const char *to_find, char *key)
{
	if (ft_isstart(key, to_find + 1))
		return (TRUE);
	else if (!ft_strcmp(to_find, "$"))
		return (TRUE);
	else if (!ft_strcmp(to_find, "${"))
		return (TRUE);
	return (FALSE);
}

void			parse_env(char **prev_b, const char *to_find, t_read *term)
{
	t_lst	*env;
	t_lst	*head;
	char	*insert;

	insert = NULL;
	env = term->shell->env;
	head = env;
	term->flag = FALSE;
	while (env->next)
	{
		if (var_is_matching(to_find, ((t_db *)(env->content))->key) == TRUE)
		{
			insert_dollar(&insert, to_find, ((t_db *)(env->content))->key);
			if (read_again(prev_b, NULL, insert, term) == FALSE)
				break ;
			term->flag = TRUE;
			ft_strdel(&insert);
		}
		env = env->next;
	}
	ft_strdel(&insert);
	if (term->flag == TRUE)
		parse_env(prev_b, to_find, term);
}
