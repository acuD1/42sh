/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:43 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:47 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_redir(t_redir *new)
{
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
}

// t_redir		*fetch_redir(t_redir *redir)
// {
// 	t_redir *new;

// 	if (!redir)
// 		return (NULL);
// 	new = redir;
// 	if (redir->op[0])
// 		new->op[0] = redir->op[0];
// 	else
// 		new->op[0] = NULL;
// 	if (redir->op[1])
// 		new->op[1] = redir->op[1];
// 	else
// 		new->op[1] = NULL;
// 	new->type = redir->type;
// 	return (new);
// }

t_analyzer	*redir_wanalyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redir_analyze(t_analyzer *anal, t_core *shell)
{
	ft_lstappend(&anal->redir_list,
		ft_lstnew(&anal->redir, sizeof(t_redir)));
	init_redir(&anal->redir);
	(void)shell;
	return (anal);
}

t_analyzer	*redirect_analyze(t_analyzer *analyzer, t_core *shell)
{
	analyzer->job.command = fill_cmd_job(analyzer->lexer, analyzer->job.command);
	analyzer->redir.type = ((t_token*)analyzer->lexer->content)->id;
	
	analyzer->state = A_REDIRECT;
	(void)shell;
	return (analyzer);
}
