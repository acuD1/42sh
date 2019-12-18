/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:37 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:53:43 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_assign(t_db *db)
{
	db->key = NULL;
	db->value = NULL;
}

t_db		*fetch_assign(t_db *assign)
{
	t_db	*new;

	if (!assign)
		return (NULL);
	new = assign;
	if (assign->key)
		new->key = assign->key;
	else
		new->key = NULL;
	if (assign->value)
		new->value = assign->value;
	else
		new->value = NULL;
	return (new);
}

t_analyzer	*ass_analyze(t_analyzer *analyzer)
{
	analyzer->db.value = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	analyzer->state = A_START;
	ft_lstappend(&analyzer->process.assign_list,
		ft_lstnew(fetch_assign(&analyzer->db), sizeof(t_db)));
	init_assign(&analyzer->db);
	return (analyzer);
}

t_analyzer	*assign_analyze(t_analyzer *anal, t_core *shell)
{
	char	*tmp;

	tmp = NULL;
	anal->job.command = fill_cmd_job(anal, 0);
	if (((t_token*)anal->lexer->content)->id == P_ASSIGN
		&& ((anal->state != A_WORD)))
	{
		anal->db.key = ft_strsub(((t_token*)anal->lexer->content)->data, 0,
			ft_strlen(((t_token*)anal->lexer->content)->data) - 1);
		anal->process.type = ((t_token*)anal->lexer->content)->id;
		anal->state = A_ASSIGN;
	}
	else
	{
		tmp = ft_strdup(((t_token*)anal->lexer->content)->data);
		get_token(anal);
		anal->job.command = fill_cmd_job(anal, 0);
		tmp = ft_strjoinf(tmp, ((t_token*)anal->lexer->content)->data, 1);
		anal->process.av = ft_add_arg_cmd_process(anal->process.av, tmp);
		anal->state = A_WORD;
		free(tmp);
	}
	(void)shell;
	return (anal);
}
