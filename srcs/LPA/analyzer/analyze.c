/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:52:47 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/25 13:02:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

t_analyzer	*end_analyze(t_analyzer *analyzer, t_core *shell)
{
	separator_analyze(analyzer, shell);
	analyzer->state = A_STOP;
	return (analyzer);
}

t_analyzer	*ionbr_analyze(t_analyzer *anal, t_core *shell)
{
	anal->state = A_IONUMBER;
	anal->job.command = fill_cmd_job(anal->lexer, anal->job.command);
	anal->redir.op[0] = ft_strdup(((t_token*)anal->lexer->content)->data);
	(void)shell;
	return (anal);
}

t_analyzer	*error_analyze(t_analyzer *anal, t_core *shell)
{
	anal->state = A_STOP;
	shell->status = 2;
	return (anal);
}

t_analyzer	*separator_analyze(t_analyzer *anal, t_core *shell)
{
	if (((t_token*)anal->lexer->content)->id == P_SEMICOLON
		|| ((t_token*)anal->lexer->content)->id == P_AND)
	{
		anal->job.type = ((t_token*)anal->lexer->content)->id;
		anal->state = A_SEPARATOR;
		return (anal = job_analyze(anal, shell));
	}
	else if (((t_token*)anal->lexer->content)->id == P_ORIF
		|| ((t_token*)anal->lexer->content)->id == P_ANDIF
		|| ((t_token*)anal->lexer->content)->id == P_PIPE)
		return (anal = add_process(anal, shell));
	else if (((t_token*)anal->lexer->content)->id == P_NEWLINE
		|| ((t_token*)anal->lexer->content)->id == P_END)
	{
		anal->job.type = ((t_token*)anal->lexer->content)->id;
		anal->state = A_SEPARATOR;
		return (anal = job_analyze(anal, shell));
	}
	return (anal);
}

void		analyzer(t_core *shell, t_lst *lexer)
{
	t_analyzer	*anal;

	anal = NULL;
	if (!lexer || !shell)
		return ;
	anal = init_analyze(anal, lexer);
	while (anal->state != A_STOP)
	{
		anal = anal->analyze[anal->state]
			[((t_token*)anal->lexer->content)->id](anal, shell);
		anal->lexer = anal->lexer->next;
	}
	free(anal->job.command);
	shell->job_list = anal->job_list;
	free(anal);
}
