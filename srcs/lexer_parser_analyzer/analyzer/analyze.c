#include "sh42.h"

void separator_analyze(t_analyzer *analyzer)
{
	e_parser_state state;

	state = ((t_token*)analyzer->lexer->tok->content)->id;
	ft_printf("SEPARATOR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
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

// t_lst *ft_lstcpy(t_lst **old)
// {
// 	t_lst *curr;
// 	t_lst *next;
// 	t_lst *new;

// 	curr = *old;
// 	if (!curr)
// 		return (NULL);
// 	while (curr)
// }

t_lst	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lst **head;

	analyzer = NULL;
	if (!shell->lexer)
		return (NULL);
	analyzer = init_analyze(analyzer, shell);
	if (parser(shell, analyzer->lexer) != TRUE)
	{
		//erreur
		return (analyzer->job_list); //shell->job = NULL;
	}
	//clean parser struct
	// while (analyzer->state != A_STOP)
	// analyzer->job_list = ft_lstnew(fetch_job(P_ERROR, NULL, &analyzer->process_list), sizeof(t_job));
	// analyzer->process_list = ft_lstnew(fetch_process(analyzer->process_cmd, P_ERROR, &analyzer->redir_list), sizeof(t_process));
	// analyzer->redir_list = ft_lstappend(&analyzer->redir_list, (ft_lstnew(fetch_redir(&analyzer->op[2], P_ERROR), sizeof(t_redir))));
	// ((t_job*)analyzer->job_list->content)->process_list = ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process));
	head = &analyzer->job_list;
	analyzer->tok_state = ((t_token*)analyzer->lexer->tok->content)->id;
	while (analyzer->state != A_STOP && (analyzer->tok_state != 20))
	{
		// ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)analyzer->lexer->tok->content)->id](analyzer);
		get_token(analyzer);
	}
	analyzer->job_list = *head;
	ft_printjoblst(analyzer->job_list);
	return (analyzer->job_list);
}
	// printf("DEBUG\n");
	// ft_printjob(&analyzer->job);
	// ft_printprocess(&analyzer->process);
	// ft_printredir(&analyzer->redir);
	// ft_lstappend(&ret, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// printlstjob(ret);
	// ft_printjobcmd(job, 0);
	//flush lexer
			// printanalyzer(analyzer);
			// ((t_process*)analyzer->job_list->content)->process_list = ft_lstappend(&analyzer->job_list->content->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
			// ((t_redir*)analyzer->job_list->content->process_list->content)->ection = ft_lstappend(&analyzer->job_list->content->process_list->content->ection, ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
			// ft_printjob(((t_job*)analyzer->job_list->content));
			// ft_printprocess(((t_process*)&analyzer->job_list->content->process_list->content));
			// ft_printredir(((t_redir*)&analyzer->process_list->content->ection->content));
