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

t_analyzer	*ass_analyze(t_analyzer *anal)
{
	char **tablo;

	tablo = NULL;
	if (!(tablo = ft_strsplit(((t_token*)anal->lexer->content)->data, "=")))
		return (anal);
	anal->db.key = ft_strdup(tablo[0]);
	if (tablo[1])
		anal->db.value = ft_strdup(tablo[1]);
	else
		anal->db.value = ft_strdup("(null)");
	ft_lstappend(&anal->process.assign_list,
		ft_lstnew(fetch_assign(&anal->db), sizeof(t_db)));
	init_assign(&anal->db);
	anal->process.type = ((t_token*)anal->lexer->content)->id;
	anal->state = A_ASSIGN;
	return (anal);
}

t_analyzer	*assign_analyze(t_analyzer *anal, t_core *shell)
{
	char	*tmp;

	tmp = NULL;
	if (((t_token*)anal->lexer->content)->id == P_ASSIGN
		&& ((anal->state != A_WORD)))
		return (anal = ass_analyze(anal));
	else
	{
		tmp = ft_strdup(((t_token*)anal->lexer->content)->data);
		anal->process.av = ft_add_arg_cmd_process(anal->process.av, tmp);
		anal->state = A_WORD;
		free(tmp);
	}
	(void)shell;
	return (anal);
}
