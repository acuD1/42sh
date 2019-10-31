#include "sh42.h"

void ionbr_analyze(t_analyzer *analyzer)
{
	// ft_printf("IONBR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->state = A_IONUMBER;
	analyzer->job.command = fill_cmd_job(analyzer, 0);
	analyzer->redir.op[0] = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	analyzer->redir.type = ((t_token*)analyzer->lexer->content)->id;
	// 	// analyzer->redir->ionumber = ft_atoi(((t_token*)lexer->content)->data);
	// }
	// analyzer->state = A_REDIRECT;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
}

void error_analyze(t_analyzer *analyzer)
{
	// ft_printf("ERROR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->state = A_STOP;
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		analyzer->state = A_STOP;
	// en theorie doit devalider la list de token et la flush
}

void separator_analyze(t_analyzer *analyzer)
{
	e_parser_state state;

	state = ((t_token*)analyzer->lexer->content)->id;
	// ft_printf("SEPARATOR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	if (state == P_SEMICOLON || state == P_AND) //jjob
	{
		analyzer->job.command = fill_cmd_job(analyzer, 0);
		analyzer->job.type = state;
		job_analyze(analyzer);
	}
	else if (state == P_ORIF || state == P_ANDIF || state == P_PIPE)
	{
		analyzer->job.command = fill_cmd_job(analyzer, 1);
		analyzer->process.type = state;
		process_analyze(analyzer);
	}
	else if (state == P_NEWLINE)
	{
		analyzer->job.type = P_END;
		job_analyze(analyzer);
	}
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
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
	while (analyzer->state != A_STOP)// && (analyzer_state != 20))
	{
		// ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)analyzer->lexer->content)->id](analyzer);
		get_token(analyzer);
	}
	shell->job_list = *head;
	shell->assign_list = analyzer->tmp_list;
}
