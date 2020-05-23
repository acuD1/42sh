/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:43 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/19 13:30:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_redir(t_redir *new)
{
	ft_bzero(new, sizeof(t_redir));
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
	new->heredoc = NULL;
}

t_analyzer	*redir_wanalyze(t_analyzer *anal, t_core *shell)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	if (anal->redir.type == P_DLESS || anal->redir.type == P_DLESSDASH)
		return (heredoc_analyzer(anal, shell));
	else
		anal->redir.op[1] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->state = A_WORD;
	return (anal = redir_analyze(anal, shell));
}

t_analyzer	*redir_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	ft_lstappend(&anal->redir_list,
		ft_lstnew(&anal->redir, sizeof(t_redir)));
	init_redir(&anal->redir);
	return (anal);
}

t_analyzer	*redirect_analyze(t_analyzer *anal, t_core *shell)
{
	(void)shell;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	if ((((t_token*)anal->lexer->content)->id == P_DLESS && anal->lexer->next
		&& ((t_token*)anal->lexer->next->content)->id == P_LESS))
		return (anal = load_heredoc_fromline(anal, shell));
	else if (((t_token*)anal->lexer->content)->id == P_ANDGREAT
		|| ((t_token*)anal->lexer->content)->id == P_ANDDGREAT)
	{
		anal->redir.op[0] = ft_strdup("&");
		if (((t_token*)anal->lexer->content)->id == P_ANDGREAT)
			anal->redir.type = P_GREAT;
		else
			anal->redir.type = P_DGREAT;
	}
	else
		anal->redir.type = ((t_token*)anal->lexer->content)->id;
	anal->state = A_REDIRECT;
	return (anal);
}
