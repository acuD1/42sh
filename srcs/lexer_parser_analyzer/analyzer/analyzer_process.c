#include "sh42.h"

void init_process(t_process *new)
{
	// ft_tabfree(new->av);
	ft_bzero(new, sizeof(t_process));
	new->type = P_START;
}

t_process *fetch_process(t_process *process)
{
	t_process *new;

	new = process;
	if (!process)
		return (NULL);
	if (process->av)
		new->av = process->av;
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
	if (process->assign_list)
		new->assign_list = process->assign_list;
	else
		new->assign_list = NULL;
	return (new);
}

t_analyzer *process_analyze(t_analyzer *analyzer, t_core *shell)
{
	// ft_printf("CREATE PROCESS state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	if (analyzer->process.av)
		ft_lstappend(&analyzer->process.assign_list, analyzer->assign_list);
	else
		ft_lstappend(&analyzer->tmp_list, analyzer->assign_list);
	analyzer->process.redir_list = analyzer->redir_list;
	ft_lstappend(&analyzer->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
	analyzer->redir_list = NULL;
	analyzer->assign_list = NULL;
	init_process(&analyzer->process);
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_SEPARATOR;
	(void)shell;
	return (analyzer);
}
