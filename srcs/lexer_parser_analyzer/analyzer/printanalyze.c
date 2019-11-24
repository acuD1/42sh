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
		printf("			cmd ");
		while(cmd[i])
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("\n");
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
		printf("\n==== ASSIGN %d ====\n", x);
		printf("[%s%s]\n", ((t_db*)assign->content)->key, ((t_db*)assign->content)->value);
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
	printf("redir state %u\n", tmp->type);
	if (tmp->op[0])
		printf("redir op[0] %s\n", tmp->op[0]);
	if (tmp->op[1])
		printf("redir op[1] %s\n", tmp->op[1]);
}

void ft_printprocess(t_process *process)
{
	t_process *tmp;

	if (!process)
		return;
	tmp = process;
	printf("process state %u\n", tmp->type);
	if (tmp->av)
		ft_printtab(tmp->av);
}

void ft_printjob(t_job *job)
{
	t_job *tmp;

	if (!job)
		return;
	tmp = job;
	printf("job state %u\n", tmp->type);
	if (tmp->command)
		printf("job command [%s]\n", tmp->command);
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
	x = 1;
	while (job)
	{
		printf("\n==== JOB %d ====\n", x);
		ft_printjob((t_job*)job->content);
		process = ((t_job*)job->content)->process_list;
		y = 1;
		while (process)
		{
			printf("\n==== PROCESS %d ====\n", y);
			ft_printprocess((t_process*)process->content);
			redir = ((t_process*)process->content)->redir_list;
			z = 1;
			while (redir)
			{
				printf("\n==== REDIR %d ====\n", z);
				ft_printredir((t_redir*)redir->content);
				z++;
				redir = redir->next;
			}
			ft_printassignlist(((t_process*)process->content)->assign_list);
			y++;
			process = process->next;
		}
		x++;
		job = job->next;
	}

}
