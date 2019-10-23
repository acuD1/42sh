#include "sh42.h"

// ft_lstappend(&lst, ft_lstnew(job, sizeof(t_job)));
t_job *fetch_job(t_job *job)
{
	t_job	*job_data;

	job_data = job;
	return (job_data);
}

t_job *init_job(void)
{
	t_job *new;

	if (!(new = (t_job*)malloc(sizeof(t_job))))
		return (NULL);
	new->cmd = NULL;
	// new->type = A_START;
	// new->redir = NULL;
	new->ection = NULL;
	// job->env = NULL;
	// job->fd->action = 0;
	// job->fd->actual = 1;
	// job->fd->wanted = 1;
	// job->status = 1;
	// job->type = A_START;
	// job->term_modes = NULL;
	return (new);
}

void ft_printjobcmd(t_job *job, int x)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!job)
	{
		ft_printf("ntm\n");
		return;
	}
	else
	{
		ft_printf("JOB N: %d\n",x);
		if (job->cmd)
		{
			j = ft_tablen(job->cmd);
			ft_printf("cmd ");
			while(job->cmd[i])
			{
				ft_printf("%s ", job->cmd[i]);
				i++;
			}
			ft_printf("\n");
		}
		// if (job->redir->op[0])
			// ft_printf("op[0] %s\n", job->redir->op[0]);
		// if (job->redir->op[1])
			// ft_printf("op[1] %s\n", job->redir->op[1]);
		// ft_printf("type %u \n", job->redir->type);
		// if (job->redir->ionumber)
			// ft_printf("IONUMBER %d\n", job->redir->ionumber);
	}
}

void printlstjob(t_lst *lst)
{
	t_job *tmp;
	t_lst *cmpp;
	int x;

	x = 1;
	tmp = NULL;
	if (!lst)
	{
		printf("cheh\n");
		return;
	}
	cmpp = lst;
	while (cmpp)
	{
		tmp = (t_job*)cmpp->content;
		ft_printjobcmd(tmp, x);
		x++;
		cmpp = cmpp->next;
	}
}