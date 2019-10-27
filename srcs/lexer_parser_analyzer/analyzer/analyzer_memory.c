#include "sh42.h"

// ft_lstappend(&lst, ft_lstnew(job, sizeof(t_job)));
t_job *fetch_job(t_job *job)
{
	t_job	*job_data;

	job_data = job;
	job_data->type = job->type;
	// job_data->cmd = job->cmd;
	job_data->command = job->command;
	job_data->process_list = job->process_list;
	job_data->process = *fetch_process(&job->process);
	// init_job(job);
	return (job_data);
}

t_redir *fetch_redir(t_redir *redir)
{
	t_redir *tmp;

	tmp = redir;
	tmp->op[0] = redir->op[0];
	tmp->op[1] = redir->op[1];
	tmp->type = redir->type;
	return (tmp);
}

t_process *fetch_process(t_process *process)
{
	t_process *tmp;

	tmp = process;
	tmp->av = process->av;
	tmp->redir = *fetch_redir(&process->redir);
	tmp->type = process->type;
	tmp->ection = process->ection;
	return (tmp);
}

void init_redir(t_redir *new)
{
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_ERROR;
	// new->fds[0] = 0;
	// new->fds[1] = 0;
}

void init_process(t_process *new)
{
	new->av = NULL;
	init_redir(&new->redir);
	new->ection = NULL;
}

void init_job(t_job *new)
{
	new->command = NULL;
	// new->cmd = NULL;
	new->type = A_START;
	init_process(&new->process);
	new->process_list = NULL;
}

void ft_printtab(char **cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (cmd)
	{
		j = ft_tablen(cmd);
		ft_printf("cmd ");
		while(cmd[i])
		{
			ft_printf("%s ", cmd[i]);
			i++;
		}
		ft_printf("\n");
	}
}

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
	else
	{
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
}

void ft_printredir(t_redir *redir)
{
	t_redir *tmp;

	if (!redir)
		return;
	else
	{
		tmp = redir;
		ft_printf("\n====REDIR====\n");
		ft_printf("state %u\n", tmp->type);
		if (tmp->op[0])	
			ft_printf("redir op[0] %s\n", tmp->op[0]);
		if (tmp->op[1])
			ft_printf("redir op[1] %s\n", tmp->op[1]);
	}
}

void ft_printprocess(t_process *process)
{
	t_process *tmp;

	if (!process)
		return;
	else
	{
		tmp = process;
		ft_printf("\n====process====\n");
		ft_printf("state %u\n", tmp->type);
		if (tmp->av)
			ft_printtab(tmp->av);
	}
}

void ft_printjob(t_job *job)
{
	t_job *tmp;

	if (!job)
		return;
	else
	{
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

}