/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:31:06 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 20:33:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	get_token(t_analyzer *analyzer)
{
	t_token	*tmp;

	if (!analyzer->lexer)
		return ;
	tmp = analyzer->lexer->content;
	ft_strdel(&(tmp->data));
	free(tmp->data);
	free(tmp);
	analyzer->lexer = analyzer->lexer->next;
}

void	ft_free_redir(t_redir *redir)
{
	ft_strdel(&(redir->op[0]));
	ft_strdel(&(redir->op[1]));
	ft_strdel(&(redir->heredoc));
	free(redir);
}

void	ft_free_redirlist(t_lst **head)
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

void	free_process_list(t_lst **head)
{
	t_lst	*ptr;
	t_lst	*next;

	if (head == NULL || *head == NULL)
		return ;
	ptr = *head;
	*head = NULL;
	while (ptr != NULL)
	{
		next = ptr->next;
		ft_free_redirlist((t_lst **)&(((t_process *)ptr->content)->redir_list));
		ft_tabdel(&(((t_process *)ptr->content)->av));
		ft_strdel(&(((t_process *)ptr->content)->bin));
		ft_strdel(&(((t_process *)ptr->content)->command));
		free(ptr->content);
		free(ptr);
		//free_assign_list
		ptr = next;
	}
}
