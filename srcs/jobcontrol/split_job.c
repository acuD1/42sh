//HEADER

#include "sh42.h"

void	split_job(t_core *shell, t_job *job)
{
	t_lst	*ptr;
	t_lst	*next;
	t_job	new_job;

	ptr = job->process_list;
	next = ptr;
	ft_bzero(&new_job, sizeof(t_job));
	if (((t_process*)ptr->content)->type == P_PIPE)
	{
		while (((t_process*)ptr->content)->type == P_PIPE)
			ptr = ptr->next;
		ptr = ptr->next;
	}
	next = ptr->next;
	if (next == NULL)
		return ;
	ptr->next = NULL;
	job->pgid = -1;
	new_job.pgid = job->pgid;
	new_job.type = P_SEMICOLON;
	new_job.process_list = job->process_list;
	rebuild_job_command(&new_job);
	job->process_list = next;
	rebuild_job_command(job);
	ft_lstappend(&(shell->launched_jobs), ft_lstnew(&new_job, sizeof(t_job)));
}
