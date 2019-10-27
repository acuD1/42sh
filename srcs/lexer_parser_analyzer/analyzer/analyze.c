#include "sh42.h"

void separator_analyze(t_analyzer *analyzer)
{
	// ft_printf("SEPARATOR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	if ((((t_token*)analyzer->lexer->tok->content)->id == 8)
		|| (((t_token*)analyzer->lexer->tok->content)->id == 4))
	{
		process_analyze(analyzer);
	}
	else
		analyzer->state = A_SEPARATOR;
	// delimite le list de token en une list ou un job
}

void redir_analyze(t_analyzer *analyzer)
{
	ft_printf("CREATE REDIR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	init_redir(&analyzer->redir);
	analyzer->state = A_START;
}
void process_analyze(t_analyzer *analyzer)
{
	if (analyzer->redir.op[1])
		redir_analyze(analyzer);
	init_process(&analyzer->process);
	ft_printf("CREATE PROCESS state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->state = A_START;
}
void job_analyze(t_analyzer *analyzer)
{
	if (analyzer->process.av)
		process_analyze(analyzer);
	init_job(&analyzer->job);
	ft_printf("CREATE JOB state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->state = A_START;
}



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
	// analyzer->job_list = ft_lstnew(fetch_job(&analyzer->job))
	head = &analyzer->job_list;
	while (analyzer->state != A_STOP && (((t_token*)analyzer->lexer->tok->content)->id != 23))
	{
		ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)analyzer->lexer->tok->content)->id](analyzer);
		// if (analyzer->state == A_CREATE_REDIR)
		// {
		// // 	ft_lstappend(&analyzer->job.process.ection, ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
		// // 	// ft_printredir(&analyzer->redir);
		// // 	init_redir(&analyzer->redir);
		// 	analyzer->state = A_START;
		// }
		// if (analyzer->state == A_CREATE_PROCESS)
		// {
		// // 	ft_lstappend(&analyzer->job.process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
		// // 	ft_printprocess(&analyzer->process);
		// // 	// init_pro cess(&analyzer->process);
		// 	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		// 		analyzer->state = A_CREATE_JOB;
		// 	else
		// 		analyzer->state = A_START;
		// }
		// if (analyzer->state == A_CREATE_JOB)
		// {
		// 	// analyzer->job.command = ft_jointab(analyzer->job.process.av);
		// 	ft_lstappend(&analyzer->job_list, ft_lstnew(fetch_job(&analyzer->job), sizeof(t_job)));
		// 	ft_printjob(&analyzer->job);
		// 	init_job(&analyzer->job);
		// 	ft_printtab(analyzer->job.process.av);
		// 	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		// 		analyzer->state = A_STOP;
		// 	else
		// 		analyzer->state = A_START;
		// }
		get_token(analyzer);
	}

	analyzer->job_list = *head;
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
