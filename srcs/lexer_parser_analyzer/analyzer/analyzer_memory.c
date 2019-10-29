#include "sh42.h"

// ft_lstappend(&lst, ft_lstnew(job, sizeof(t_job)));

void	get_token(t_analyzer *analyzer)
{
	if (!analyzer->lexer->tok)
		return ;
	analyzer->lexer->tok = analyzer->lexer->tok->next;
	//free(analyzer->lexer->tok);
}

void printanalyzer(t_analyzer *analyzer)
{
	t_analyzer *tmp;

	tmp = analyzer;
	if (!tmp)
		return;
	ft_printf("state %u\n", tmp->state);
	ft_printf("tok actuel %s et son type %u\n", ((t_token*)tmp->lexer->tok->content)->data, ((t_token*)tmp->lexer->tok->content)->id);
	// if (tmp->process)
	// {
	// 	ft_printf("\n====PROCESS====\n");
	// 	ft_printf("state %u\n", tmp->process.type);
		// if (tmp->process.redir.op[0])
		// 	printf("redir op[0] %s\n", tmp->process.redir.op[0]);
		// if (tmp->process.redir.op[1])
		// 	printf("redir op[1] %s\n", tmp->process.redir.op[1]);
		// if (tmp->process.av)
		// 	ft_printjobcmd(tmp->process.av, 0);
	// }
	// if (tmp->job)
	// {
	// 	ft_printf("\n====JOB====\n");
	// 	ft_printf("state %u\n", tmp->job.type);
	// 	if (tmp->job.command)
	// 		ft_printf("job command %s\n", tmp->job.command);
	// 	if (tmp->job.cmd)
	// 		ft_printjobcmd(tmp->job.cmd, 0);
	// }
}

void ft_printredir(t_redir *redir)
{
	t_redir *tmp;

	if (!redir)
		return;
	tmp = redir;
	ft_printf("\n==== REDIR====\n");
	ft_printf("state %u\n", tmp->type);
	if (tmp->op[0])	
		ft_printf("redir op[0] %s\n", tmp->op[0]);
	if (tmp->op[1])
		ft_printf("redir op[1] %s\n", tmp->op[1]);
}

void ft_printprocess(t_process *process)
{
	t_process *tmp;

	if (!process)
		return;
	tmp = process;
	ft_printf("\n====process====\n");
	ft_printf("state %u\n", tmp->type);
	if (tmp->av)
		ft_printtab(tmp->av);
}

void ft_printjob(t_job *job)
{
	t_job *tmp;

	if (!job)
		return;
	tmp = job;
	ft_printf("\n====JOB====\n");
	ft_printf("state %u\n", tmp->type);
	if (tmp->command)
		ft_printf("job command %s\n", tmp->command);
	// if (tmp->cmd)
		// ft_printjobcmd(tmp->cmd, 0);
	// if (tmp->process != NULL)
	// {
	// 	ft_printf("\n====JOB PROCESS====\n");
	// 	ft_printprocess(&tmp->process);
	// }

	// if (job->redir->op[0])
		// ft_printf("op[0] %s\n", job->redir->op[0]);
	// if (job->redir->op[1])
		// ft_printf("op[1] %s\n", job->redir->op[1]);
	// ft_printf("type %u \n", job->redir->type);
	// if (job->redir->ionumber)
			// ft_printf("IONUMBER %d\n", job->redir->ionumber);

}