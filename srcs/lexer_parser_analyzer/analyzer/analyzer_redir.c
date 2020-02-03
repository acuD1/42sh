/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:43 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 18:03:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			init_redir(t_redir *new)
{
	ft_bzero(new, sizeof(t_redir));
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
	new->heredoc = NULL;
}

/*
t_redir		*fetch_redir(t_redir *redir)
{
	t_redir *new;

	if (!redir)
		return (NULL);
	new = redir;
	if (redir->op[0])
		new->op[0] = redir->op[0];
	else
		new->op[0] = NULL;
	if (redir->op[1])
		new->op[1] = redir->op[1];
	else
		new->op[1] = NULL;
	new->type = redir->type;
	return (new);
}
*/

static t_analyzer	*heredoc_analyzer(t_analyzer *anal, t_core *shell)
{
	anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	if (!shell->term.history_index)
		anal->redir.heredoc = load_heredoc(shell, anal->redir.op[1]);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer			*redir_wanalyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	if (anal->redir.type == P_DLESS)
		return (heredoc_analyzer(anal, shell));
	else
		anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer			*redir_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	ft_lstappend(&anal->redir_list,
		ft_lstnew(&anal->redir, sizeof(t_redir)));
	init_redir(&anal->redir);
	return (anal);
}

t_analyzer			*redirect_analyze(t_analyzer *analyzer, t_core *shell)
{
	(void)shell;
	analyzer->job.command = fill_cmd_job(analyzer->lexer, analyzer->job.command);
	analyzer->redir.type = ((t_token*)analyzer->lexer->content)->id;
	analyzer->state = A_REDIRECT;
	return (analyzer);
}
