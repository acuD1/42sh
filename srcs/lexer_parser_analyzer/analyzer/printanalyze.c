#include "sh42.h"

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

void ft_printassignlist(t_lst *lst)
{
	t_lst *assign;
	int x = 0;

	if (!lst)
		return;
	assign = lst;

	while (assign)
	{
		ft_printf("\n==== ASSIGN %d ====\n", x);
		ft_printf("[%s%s]\n", ((t_db*)assign->content)->key, ((t_db*)assign->content)->value);
		assign = assign->next;
		x++;
	}
}

void ft_printredir(t_redir *redir)
{
	t_redir *tmp;

	if (!redir)
		return;
	tmp = redir;
	ft_printf("redir state %u\n", tmp->type);
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
	ft_printf("process state %u\n", tmp->type);
	if (tmp->av)
		ft_printtab(tmp->av);
}

void ft_printjob(t_job *job)
{
	t_job *tmp;

	if (!job)
		return;
	tmp = job;
	ft_printf("job state %u\n", tmp->type);
	if (tmp->command)
		ft_printf("job command [%s]\n", tmp->command);
}

void ft_printjoblst(t_lst *list)
{
	t_lst *job;
	t_lst *process;
	t_lst *redir;
	int x , y , z;

	if (!list)
		return;
	job = list;
	x = 0;
	while (job)
	{
		ft_printf("\n==== JOB %d ====\n", x);
		ft_printjob((t_job*)job->content);
		process = ((t_job*)job->content)->process_list;
		y = 0;
		while (process)
		{
			ft_printf("\n==== PROCESS %d ====\n", y);
			ft_printprocess((t_process*)process->content);
			redir = ((t_process*)process->content)->redir_list;
			z = 0;
			while (redir)
			{
				ft_printf("\n==== REDIR %d ====\n", z);
				ft_printredir((t_redir*)redir->content);
				z++;
				redir = redir->next;
			}
			y++;
			process = process->next;
		}
		x++;
		job = job->next;
	}

}
