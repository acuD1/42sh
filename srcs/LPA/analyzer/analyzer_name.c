/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/06 22:45:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_analyzer	*process_word_analyze(t_analyzer *anal)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	ft_lstappend(&anal->process.tok_list, ft_lstnew(fetch_token(&anal->tok,
		((t_token*)anal->lexer->content)->id,
		((t_token*)anal->lexer->content)->data), sizeof(t_token)));
	return (anal);
}

t_analyzer	*cmd_analyze(t_analyzer *anal, t_core *shell)
{
	if (anal->state == A_REDIRECT)
		return (anal = redir_wanalyze(anal, shell));
	else
		anal = process_word_analyze(anal);
	anal->state = A_WORD;
	return (anal);
}
