#include "sh42.h"

void init_process(t_process *new)
{
	// ft_tabfree(new->av);
	new->av = NULL;
	new->type = P_START;
	new->redir_list = NULL;
}

t_process *fetch_process(t_process *process)
{
	t_process *new;

	new = process;
	if (!process)
		return (NULL);
	if (process->av)
		new->av = ft_tabcopy(new->av, process->av);
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

void process_analyze(t_analyzer *analyzer)
{
	// ft_printf("CREATE PROCESS state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->process.redir_list = analyzer->redir_list;
	ft_lstappend(&analyzer->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
	analyzer->redir_list = NULL;
	init_process(&analyzer->process);
	if (((t_token*)analyzer->lexer->tok->next->content)->id == 20) //&& !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_SEPARATOR;
}
