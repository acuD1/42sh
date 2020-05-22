/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/09 17:24:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				init_assign(t_db *db)
{
	db->key = NULL;
	db->value = NULL;
	db->type = 0;
}

static t_analyzer	*split_and_create_assign_token(t_analyzer *anal)
{
	ft_lstappend(&anal->process.assign_list,
		ft_lstnew(fetch_db(&anal->db,
		((t_token*)anal->lexer->content)->data,
		INTERNAL_VAR), sizeof(t_db)));
	init_assign(&anal->db);
	anal->process.type = ((t_token*)anal->lexer->content)->id;
	anal->state = A_ASSIGN;
	return (anal);
}

t_analyzer			*assign_analyze(t_analyzer *anal, t_core *shell)
{
	if (((t_token*)anal->lexer->content)->id == P_ASSIGN
		&& ((anal->state != A_WORD)))
	{
		anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
		return (anal = split_and_create_assign_token(anal));
	}
	else
	{
		anal = process_word_analyze(anal);
		anal->state = A_WORD;
	}
	(void)shell;
	return (anal);
}
