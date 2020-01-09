/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:40:31 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/09 16:03:03 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		get_token(t_analyzer *analyzer)
{
	t_token	*tmp;

	if (!analyzer->lexer)
		return ;
	tmp = analyzer->lexer->content;
	free(tmp->data);
	free(tmp);
	analyzer->lexer = analyzer->lexer->next;
}

void		ft_free_redir(t_redir *redir)
{
	ft_strdel(&(redir->op[0]));
	ft_strdel(&(redir->op[1]));
	ft_strdel(&(redir->heredoc));
	free(redir);
}

void		ft_free_redirlist(t_lst **head)
{
	t_lst	*ptr;
	t_lst	*next;

	if (head == NULL || *head == NULL)
		return ;
	ptr = *head;
	while (ptr)
	{
		next = ptr->next;
		ft_free_redir(ptr->content);
		free(ptr);
		ptr = next;
	}
}

void		free_process_list(t_lst **head)
{
	t_lst *ptr;
	t_lst *next;

	if (head == NULL || *head == NULL)
		return ;
	*head = NULL;
	ptr = *head;
	while (ptr != NULL)
	{
		next = ptr->next;
		ft_free_redirlist(&(((t_process*)ptr->content)->redir_list));
		ft_tabdel(&(((t_process*)ptr->content)->av));
		//free_assign_list
		ptr = next;
	}

}
