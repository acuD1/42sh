#include "sh42.h"

// void ft_freelst(t_lst **head)
// {
// 	t_lst *next;
// 	t_lst *curr;

// 	if (!*head)
// 		return;
// 	curr = *head;
// 	next = curr->next;
// 	while (curr)
// 	{
// 		curr = curr->next;
// 		free(next);
// 		next = curr->next;
// 	}
// 	free(curr);
// }

void ft_printjoblst(t_lst *list)
{
	t_lst *job;
	t_lst *process;
	t_lst *redir;

	if (!list)
		return;
	job = list;
	while (job)
	{
		process = ((t_job*)job->content)->process_list;
		while (process)
		{
			redir = ((t_process*)process->content)->redir_list;
			while (redir)
			{
				ft_printredir((t_redir*)redir->content);
				// ft_printf("redir %d: op[0] %s op[1] %s type %u\n", ((t_redir*)redir->content)->op[0], ((t_redir*)redir->content)->op[1], ((t_redir*)redir->content)->type);
				redir = redir->next;
			}
			ft_printprocess((t_process*)process->content);
			process = process->next;
		}
		ft_printjob((t_job*)job->content);
		job = job->next;
	}

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