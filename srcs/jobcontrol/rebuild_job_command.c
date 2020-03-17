#include "sh42.h"

void	rebuild_job_command(t_job *job)
{
	t_process	*process;
	t_lst		*ptr;
	char		*tmp;
	int			skip;

	ptr = job->process_list;
	ft_strdel(&(job->command));
	while (ptr)
	{
		process = ptr->content;
		if (ft_strncmp(process->command, "&& ", 3) == 0
			|| ft_strncmp(process->command, "|| ", 3) == 0)
			skip = 3;
		else if (ft_strncmp(process->command, "| ", 2) == 0)
			skip = 2;
		else
			skip = 0;
		tmp = ft_strjoin(job->command, process->command + skip);
		ft_strdel(&(job->command));
		job->command = tmp;
		ptr = ptr->next;
	}
}
