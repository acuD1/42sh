#include "sh42.h"

void	get_token(t_analyzer *analyzer)
{
	t_token *tmp;

	if (!analyzer->lexer)
		return ;
	tmp = analyzer->lexer->content;
	free(tmp->data);
	free(tmp);
	analyzer->lexer = analyzer->lexer->next;
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
	int i;

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
			ft_freedblist(&pro->assign_list);
			if (pro->av)
			{
				i = 0;
				while (pro->av[i])
				{
					free(pro->av[i]);
					i++;
				}
			}
		}
		tmp = process;
		process = process->next;
		free(tmp);
	}
}
