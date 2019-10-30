#include "sh42.h"

void init_job(t_job *new)
{
	new->command  = ft_strnew(0);
	new->type = P_START;
	new->process_list = NULL;
}

t_job *fetch_job(t_job *job)
{
	t_job *new;

	if (!job)
		return (NULL);
	new = job;
	new->type = job->type;
	if (job->command)
		new->command = job->command;
	else
		new->command = NULL;
	if (job->process_list)
		new->process_list = job->process_list;
	else
		new->process_list = NULL;
	return (new);
}

t_lst *ft_create_job(char *cmd, e_parser_state id, t_lst *list)
{
	t_lst		*new;
	t_job *job;

	job = NULL;
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(job = (t_job*)malloc(sizeof(t_job))))
		return (NULL);
	job->type = id;
	job->process_list = list;
	job->command = cmd;
	new->content = (void*)fetch_job(job);
	return (new);
}

void job_analyze(t_analyzer *analyzer)
{
	process_analyze(analyzer);	
	ft_printf("CREATE JOB state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->job.process_list = analyzer->process_list;
	ft_lstappend(&analyzer->job_list ,ft_lstnew(fetch_job(&analyzer->job), sizeof(t_job)));
	analyzer->process_list = NULL;
	init_job(&analyzer->job);
	// ft_free_processlist(&analyzer->process_list);
	// ft_lstappend(&analyzer->job_list, ft_create_job(analyzer.job->cmd, ((t_token*)analyzer->lexer->tok->content)->id, &analyzer->job->content->process_list));

	// ft_lstadd(&analyzer->job_list, ft_create_job(analyzer->job_cmd, ((t_token*)analyzer->lexer->tok->content)->id, analyzer->process_list));
	// free(analyzer->job_cmd);
	// ft_free_processlist(&analyzer->process_list);
	// free_analyze(analyzer);
	// init_job(analyzer->job);
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_STOP;
	// free(job);
}

// void free_analyze(t_analyzer *analyzer)
// {
// 	t_lst *tmp;

// 	tmp = analyzer->redir_list;
// 	while (tmp)
// 	{
// 		tmp = analyzer->redir_list->next;
// 		ft_free_redir((t_redir*)analyzer->redir_list->content);
// 		free(analyzer->redir_list);
// 	}
// 	tmp = analyzer->process_list;
// 	while (tmp)
// 	{
// 		tmp = analyzer->process_list->next;
// 		ft_free_processlist(&analyzer->process_list);
// 		free(analyzer->process_list);
// 	}
// 	if (analyzer->job_cmd)
// 		free(analyzer->job_cmd);
// 	if (*analyzer->process_cmd)
// 		ft_tabfree(analyzer->process_cmd);
// 	if (*analyzer->op)
// 	{
// 		free(&analyzer->op[0]);
// 		free(&analyzer->op[1]);
// 	}
// }
