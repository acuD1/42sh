#include "sh42.h"

void	get_token(t_analyzer *analyzer)
{
	if (!analyzer->lexer->tok)
		return ;
	analyzer->lexer->tok = analyzer->lexer->tok->next;
	//free(analyzer->lexer->tok);
}

void ft_free_redir(t_redir *redir)
{
	free(redir->op[0]);
	free(redir->op[1]);
	free(redir);
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
