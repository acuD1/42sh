/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:53:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 18:01:22 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				init_assign(t_db *db)
{
	db->key = NULL;
	db->value = NULL;
}

// ??
/*
static t_db			*fetch_assign(t_db *assign)
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
}*/

// PUTIN WTF
static t_analyzer	*ass_analyze(t_analyzer *anal)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ((t_token*)anal->lexer->content)->data;
	while (str[i] != '=')
		i++;
	anal->db.key = ft_strsub(str, 0, i);
	j = i++;
	while (str[j])
		j++;
	anal->db.value = ft_strsub(str, i, j - i);
	ft_lstappend(&anal->process.assign_list,
		ft_lstnew(&anal->db, sizeof(t_db)));
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
	{
		anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
		return (anal = ass_analyze(anal));
	}
	else
	{
		anal = process_word_analyze(anal);
		anal->state = A_WORD;
	}
	(void)shell;
	return (anal);
}
