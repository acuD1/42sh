#include "sh42.h"

void separator_analyze(t_analyzer *analyzer)
{
	e_parser_state state;

	state = ((t_token*)analyzer->lexer->tok->content)->id;
	// ft_printf("SEPARATOR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	if (state == P_SEMICOLON || state == P_AND) //jjob
	{
		analyzer->job.command = fill_cmd_job(analyzer);
		analyzer->job.type = state;
		job_analyze(analyzer);
	}
	else if (state == P_ORIF || state == P_ANDIF)
	{
		analyzer->job.command = fill_cmd_job(analyzer);
		analyzer->process.type = state;
		process_analyze(analyzer);
	}
	else if (state == P_NEWLINE)
	{
		analyzer->job.type = P_END;
		job_analyze(analyzer);
	}
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_SEPARATOR;
}

void analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lst **head;

	analyzer = NULL;
	if (!shell->lexer)
		return;
	analyzer = init_analyze(analyzer, shell);
	head = &analyzer->job_list;
	while (analyzer->state != A_STOP)// && (analyzer->tok_state != 20))
	{
		// ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)analyzer->lexer->tok->content)->id](analyzer);
		get_token(analyzer);
	}
	shell->job_list = *head;
	shell->assign_list = analyzer->assign_list;
}
