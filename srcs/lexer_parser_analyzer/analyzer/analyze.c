#include "sh42.h"

void separator_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("SEPARATOR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// if ((((t_token*)analyzer->lexer->tok->content)->id == 0)
	// 	|| (((t_token*)analyzer->lexer->tok->content)->id == 6))
	// {
	// 	analyzer->job_type = ((t_token*)analyzer->lexer->tok->content)->id;
	// 	job_analyze(analyzer);
	// }
	// else
		(void)job;
		analyzer->state = A_SEPARATOR;
	// delimite le list de token en une list ou un job
}

t_lst	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lst **head;
	t_job job;

	analyzer = NULL;
	if (!shell->lexer)
		return (NULL);
	analyzer = init_analyze(analyzer, shell);
	init_job(&job);
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
	while (analyzer->state != A_STOP && (analyzer->tok_state != 20))
	{
		ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, analyzer->tok_state ,((t_token*)analyzer->lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][analyzer->tok_state](analyzer, &job);
		get_token(analyzer);
		analyzer->tok_state = ((t_token*)analyzer->lexer->tok->content)->id;
	}
	analyzer->job_list = *head;
	// ft_printjoblst(analyzer->job_list);
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
