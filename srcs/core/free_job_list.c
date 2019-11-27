/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:10:56 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/26 22:32:51 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_redir_list(t_lst *redir)
{
	t_lst		*next;
	t_redir		*ptr;
	
	next = NULL;
	ptr = NULL;
	while (redir)
	{
		/* saving before deleting t_lst link*/
		next = redir->next;
		ptr = ((t_redir*)redir->content);
		ft_bzero(redir, sizeof(t_lst));

		/* freeing t_lst link */
		free(redir);

		/* freeing content */
		ft_strdel(&(ptr->op[0]));
		ft_strdel(&(ptr->op[1]));
		ft_bzero(ptr, sizeof(redir));
		redir = next
	}
}

void	free_process_list(t_lst *process)
{
	t_lst		*next;
	t_process	*ptr;

	while (process)
	{
		/* saving before deleting t_lst link*/
		next = process->next;
		ptr = ((t_process*)process->content);
		ft_bzero(process, sizeof(t_lst));

		/* freeing t_lst link */
		free(process);

		/* freeing t_process content */
		ft_strdel(&(ptr->bin));
		free_redir_list(ptr->redir_list);
		//free_assign_list(ptr->assign_list);
		ft_tabfree(ptr->av);
		ft_bzero(ptr, sizeof(t_process));
		process = process->next
	}
}

void	free_job_list(t_lst *jobs)
{

}
