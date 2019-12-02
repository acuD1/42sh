/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:52:47 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:53:25 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_analyzer			*end_analyze(t_analyzer *analyzer, t_core *shell)
{
	separator_analyze(analyzer, shell);
	analyzer->state = A_STOP;
	return (analyzer);
}

t_analyzer			*ionbr_analyze(t_analyzer *anal, t_core *shell)
{
	anal->state = A_IONUMBER;
	anal->job.command = fill_cmd_job(anal, 0);
	anal->redir.op[0] = ft_strdup(((t_token*)anal->lexer->content)->data);
	anal->redir.type = ((t_token*)anal->lexer->content)->id;
	(void)shell;
	return (anal);
}

t_analyzer			*error_analyze(t_analyzer *anal, t_core *shell)
{
	anal->state = A_STOP;
	if (anal->lexer->next
		&& !ft_strcmp("(null)", ((t_token*)anal->lexer->next->content)->data))
		anal->state = A_STOP;
	(void)shell;
	return (anal);
}

t_analyzer			*separator_analyze(t_analyzer *analyzer, t_core *shell)
{
	e_pstate		state;

	state = P_ERROR;
	state = ((t_token*)analyzer->lexer->content)->id;
	if (state == P_SEMICOLON || state == P_AND)
	{
		analyzer->job.command = fill_cmd_job(analyzer, 0);
		analyzer->job.type = state;
		return (analyzer = job_analyze(analyzer, shell));
	}
	else if (state == P_ORIF || state == P_ANDIF || state == P_PIPE)
	{
		analyzer->job.command = fill_cmd_job(analyzer, 1);
		analyzer->process.type = state;
		analyzer->state = A_SEPARATOR;
		return (analyzer = process_analyze(analyzer, shell));
	}
	else if (state == P_NEWLINE || state == P_END)
	{
		analyzer->job.type = P_END;
		return (analyzer = job_analyze(analyzer, shell));
	}
	analyzer->state = A_SEPARATOR;
	return (analyzer);
}

void				analyzer(t_core *shell, t_lst *lexer)
{
	t_analyzer		*anal;

	anal = NULL;
	if (!lexer || !shell)
		return ;
	anal = init_analyze(anal, lexer);
	while (anal->state != A_STOP)
	{
		anal = anal->analyze[anal->state]
			[((t_token*)anal->lexer->content)->id](anal, shell);
		get_token(anal);
	}
	free(anal->job.command);
	shell->job_list = anal->job_list;
	free(anal);
}
