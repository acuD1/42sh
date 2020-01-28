/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:54:18 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/28 20:34:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_analyzer	*escape_sequence_analyzer(t_analyzer *analyzer)
{
	/*
	char	*str;

	str = NULL;
	str = ft_strnew(0);
	while (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
		&& ((t_token*)analyzer->lexer->next->content)->id != P_END)
	{
		if (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ
			|| ((t_token*)analyzer->lexer->content)->id == P_SEMICOLON)
			get_token(analyzer);
		if (((t_token*)analyzer->lexer->next->content)->id == P_END)
			break ;
		str = ft_strjoinf(str, ((t_token*)analyzer->lexer->content)->data, 1);
		get_token(analyzer);
	}
	printf("{%s}\n", str);
	ft_strdel(&(((t_token*)analyzer->lexer->content)->data));
	((t_token*)analyzer->lexer->content)->data = ft_strdup(str);
	ft_strdel(&(str));
	analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av,
		((t_token*)analyzer->lexer->content)->data);
	((t_token*)analyzer->lexer->content)->id = P_ESCSEQ;
	*/
	return (analyzer);
}

t_analyzer	*process_word_analyze(t_analyzer *anal)
{
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->process.command = fill_cmd_job(anal->lexer, anal->process.command);
	ft_lstappend(&anal->process.tok_list, ft_lstnew(fetch_token(&anal->tok,
		((t_token*)anal->lexer->content)->id, ((t_token*)anal->lexer->content)->data), sizeof(t_token)));
	return (anal);
}

t_analyzer	*cmd_analyze(t_analyzer *anal, t_core *shell)
{
	if (anal->state == A_REDIRECT)
			return (anal = redir_wanalyze(anal, shell));
	/*
	else if (((t_token*)anal->lexer->content)->id == P_ESCSEQ)
		anal = escape_sequence_anal(anal);
	*/
	else
		anal = process_word_analyze(anal);
	anal->state = A_WORD;
	return (anal);
}
