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
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"cmd {");
		while(cmd[i])
		{
			dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"%s ", cmd[i]);
			i++;
		}
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"}\n");
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
		debug_ailleurs("/dev/ttys002", "============= ASSIGN ============\n");
		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->key);
		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->value);
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
	dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"redir state %u\n", tmp->type);
	if (tmp->op[0])
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "redir op[0] %s\n", tmp->op[0]);
	if (tmp->op[1])
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "redir op[1] %s\n", tmp->op[1]);
}

void ft_printprocess(t_process *process)
{
	t_process *tmp;

	if (!process)
		return;
	tmp = process;
	dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"process state %u\n", tmp->type);
	if (tmp->av)
		ft_printtab(tmp->av);
}

void ft_printjob(t_job *job)
{
	t_job *tmp;

	if (!job)
		return;
	tmp = job;
	dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"job state %u\n", tmp->type);
	if (tmp->command)
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"job command [%s]\n", tmp->command);
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
		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "\n==== JOB %d ====\n", x);
		ft_printjob((t_job*)job->content);
		process = ((t_job*)job->content)->process_list;
		y = 1;
		while (process)
		{
			dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "\n==== PROCESS %d ====\n", y);
			ft_printprocess((t_process*)process->content);
			redir = ((t_process*)process->content)->redir_list;
			z = 1;
			while (redir)
			{
				dprintf(getlefdpour_debug_ailleurs("/dev/ttys002") ,"\n==== REDIR %d ====\n", z);
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
