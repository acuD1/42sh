#include "sh42.h"

void init_process(t_process *new)
{
	new->av = NULL;
	// init_redir(&new->redir);
	new->redir_list = NULL;
}

void ft_free_processlist(t_lst **head) ///t_process *process)
{
	t_lst *tmp;
	t_lst *tmpp;
	t_lst *process;
	// t_lst *redir;
	t_process *pro;
	t_redir		*red;

	process = NULL;
	pro = NULL;
	red = NULL;
	tmp = NULL;
	tmpp = NULL;
	if (!*head)
		return;
	process = *head;
	while (process)
	{
		if (process->content)
		{
			pro = (t_process*)process->content;
			// if (pro->redir_list->content)
			// {
			// 	redir = pro->redir_list;
			// 	while (redir)
			// 	{
			// 		red = (t_redir*)redir->content;
			// 		ft_free_redir(red);
			// 		tmp = redir;
			// 		redir = redir->next;
			// 		free(tmp);
			// 	}
			// }
			if (*pro->av)
				ft_tabfree(pro->av);
		}
		tmpp = process;
		process = process->next;
		free(tmpp);
	}

	// }
	// if (process->redir_list)
	// {
	// 	tmp = process->redir_list;
	// 	while (tmp)
	// 	{
	// 		tmp = process->redir_list->next;
	// 		ft_free_redir((t_redir*)tmp->content);
	// 		free(process->redir_list);
	// 	}
	// }
}

t_process *fetch_process(t_process *process, char **av, e_parser_state type, t_lst *redir_list)
{
	//free ancien av
	if (*av)
		process->av = ft_tabcopy(process->av, av);
	else
		process->av = NULL;
	if (type)
		process->type = type;
	else
		process->type = P_START;
	if (redir_list)
		process->redir_list = redir_list;
	else
		process->redir_list = NULL;
	return (process);
}


t_lst *ft_create_process(char **cmd, e_parser_state id, t_lst *list)
{
	t_lst		*new;
	t_process *process;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(process = (t_process*)malloc(sizeof(t_process))))
		return (NULL);
	new->content = (void*)fetch_process(process, cmd, id, list);
	return (new);
}

void process_analyze(t_analyzer *analyzer, t_job *job)
{

	ft_printf("CREATE PROCESS state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// redir_analyze(analyzer);
	// process->av = analyzer->process_cmd;
	// process->type = ((t_token*)analyzer->lexer->tok->content)->id;
	// process->redir_list = analyzer->redir_list;
	// ft_lstappend(&analyzer->process_list, ft_lstnew(&process, sizeof(t_process)));
	// ft_printtab(analyzer->process_cmd);
	// ft_lstadd(&analyzer->process_list, ft_create_process(analyzer->process_cmd, ((t_token*)analyzer->lexer->tok->content)->id, analyzer->redir_list));
	// ft_tabfree(analyzer->process_cmd);
	// ft_printprocess((t_process*)analyzer->process_list->content);
	// init_process(analyzer->process);
	// if (((t_token*)analyzer->lexer->tok->next->content)->id == 20) //&& !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
	// {
	// 	job_analyze(analyzer);
	// 	analyzer->state = A_STOP;
		(void)job;
	// }
	// else
		analyzer->state = A_START;
	// free(process);
}

	// if (analyzer->process.av)
	// analyzer->job.command = getjoblistcmdtab(analyzer->job.process_list);
	// ft_printf("strp %s\n", analyzer->job.command);
	// init_job(&analyzer->job);
		// process_analyze(analyzer);


