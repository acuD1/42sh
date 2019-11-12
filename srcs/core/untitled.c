#include "sh42.h"

			// int i;

			// i = 0;
			// while (((t_process*)((t_job*)job_list->content)->process_list->content)->av[i])
			// {
			// 	shell->tokens = ft_strdup(((t_process*)((t_job*)job_list->content)->process_list->content)->av);
			// 	printf("[%s]\n",shell->tokens);
			// 	free(shell->tokens);
			// 	i++;
			// }			

uint8_t	exec_from_shell_job_list(t_lst *job_list, t_core *shell)
{
	t_lst *tmp;
	t_lst **head;

	if (!job_list)
		return (FALSE);
	tmp = job_list;
	head = &job_list;
	while (tmp)
	{
		if (((t_process*)((t_job*)tmp->content)->process_list->content)->av)
		{
			shell->tokens = ((t_process*)((t_job*)tmp->content)->process_list->content)->av;
			if (shell->tokens)
				exec_process(shell, shell->env);
		}
		tmp = tmp->next;
	}
	job_list = *head;
	return (TRUE);
}
