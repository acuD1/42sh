/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:03:59 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 00:31:51 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	fill_var_lst(char *var, t_auto_comp *ac)
{
	char	*tmp;

	tmp = NULL;
	if (ac->type == AC_BRACKET)
		tmp = ft_strjoin("${", var);
	else
		tmp = ft_strjoin("$", var);
	if (ac->type == AC_BRACKET)
		tmp = ft_strjoinf(tmp, "} ", 1);
	else
		tmp = ft_strjoinf(tmp, " ", 1);
	ft_lstappend(&ac->lst, ft_lstnew(tmp, sizeof(char) * (ft_strlen(tmp) + 1)));
	ac->lst_size++;
	ac->max_len = get_max_len(ac->max_len, ft_strlen(tmp));
	ft_strdel(&tmp);
}

void		ac_variable(char *input, t_auto_comp *ac, t_core *shell)
{
	t_lst	*env;
	size_t	input_len;

	env = shell->env;
	input_len = ft_strlen(input);
	ac->ws_col = (size_t)shell->term.ws_col;
	while (env != NULL)
	{
		if ((!*input || ft_isstart(((t_db *)(env->content))->key, input))
			&& (((t_db *)(env->content))->type & INTERNAL_VAR
				|| (((t_db *)(env->content))->type & EXPORT_VAR)))
			fill_var_lst(((t_db *)(env->content))->key, ac);
		env = env->next;
	}
}
