#include "sh42.h"

void init_process(t_process *new)
{
	new->av = NULL;
	new->type = P_START;
	new->redir_list = NULL;
}

void ft_free_redirlist(t_lst **head)
{
	t_lst *curr;
	t_lst *next;

	if (!*head)
		return;
	curr = *head;
	next = NULL;
	while (curr)
	{
		if (curr->content)
			ft_free_redir((t_redir*)curr->content);
		next = curr;
		curr = curr->next;
		free(next);
	}
}

void ft_free_processlist(t_lst **head) ///t_process *process)
{
	t_lst *tmp;
	t_lst *process;
	t_process *pro;

	process = NULL;
	pro = NULL;
	tmp = NULL;
	if (!*head)
		return;
	process = *head;
	while (process)
	{
		if (process->content)
		{
			pro = (t_process*)process->content;
			ft_free_redirlist(&pro->redir_list);
			if (pro->av)
				ft_tabfree(pro->av);
		}
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

t_process *fetch_process(t_process *process)
{
	t_process *new;

	new = process;
	if (!process)
		return (NULL);
	if (process->av)
	{
		ft_printf("totot\n");
		new->av = ft_tabcopy(new->av, process->av);
		// ft_tabfree(process->av);
	}
	else
		new->av = NULL;
	if (process->type)
		new->type = process->type;
	else
		new->type = P_START;
	if (process->redir_list)
		new->redir_list = process->redir_list;
	else
		new->redir_list = NULL;
	return (new);
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
	process->av = cmd;
	process->type = id;
	process->redir_list = list;
	new->content = (void*)fetch_process(process);
	return (new);
}

void process_analyze(t_analyzer *analyzer)
{
	ft_printf("CREATE PROCESS state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->process.redir_list = analyzer->redir_list;
	ft_lstappend(&analyzer->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
	// ((t_process*)analyzer->process_list->content)->redir_list = &*analyzer->redir_list;
	// ft_free_redirlist(&analyzer->redir_list);
	analyzer->redir_list = NULL;
	init_process(&analyzer->process);
	// process->av = analyzer->process_cmd;
	// process->type = ((t_token*)analyzer->lexer->tok->content)->id;
	// process->redir_list = analyzer->redir_list;
	// ft_lstappend(&analyzer->process_list, ft_lstnew(&process, sizeof(t_process)));
	// if (job->process_list)// ft_printtab(analyzer->process_cmd);
		// ft_lstadd(&job->process_list, ft_create_process(NULL, ((t_token*)analyzer->lexer->tok->content)->id, NULL));
	// ft_tabfree(analyzer->process_cmd);
	// ft_printprocess((t_process*)analyzer->process_list->content);
	// init_process(analyzer->process);
	// if (((t_token*)analyzer->lexer->tok->next->content)->id == 20) //&& !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
	// {
	// 	job_analyze(analyzer);
	// 	analyzer->state = A_STOP;
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


