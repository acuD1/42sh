#include "sh42.h"

void init_job(t_job *new)
{
	new->command  = ft_strnew(0);
	new->type = P_END;
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

t_analyzer *job_analyze(t_analyzer *analyzer, t_core *shell)
{
	analyzer = process_analyze(analyzer, shell);
	// ft_printf("CREATE JOB state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->job.process_list = analyzer->process_list;
	ft_lstappend(&analyzer->job_list ,ft_lstnew(fetch_job(&analyzer->job), sizeof(t_job)));
	analyzer->process_list = NULL;
	init_job(&analyzer->job);
	// if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		// analyzer->state = A_STOP;
	// else
		analyzer->state = A_START;
	return (analyzer);
}
