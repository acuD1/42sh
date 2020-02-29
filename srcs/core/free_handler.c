/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:27:32 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/19 18:47:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		free_db(t_lst *db)
{
	t_lst	*tmp;

	while (db)
	{
		ft_strdel(&((t_db*)(db->content))->key);
		ft_strdel(&((t_db*)(db->content))->value);
		free(db->content);
		tmp = db;
		db = db->next;
		free(tmp);
	}
}

void		free_prompt(t_core *shell)
{
	ft_strdel(&shell->term.buffer);
	ft_freejoblist(&shell->job_list);
}

static void	free_history(t_read *term)
{
	t_lst	*tmp;

	while (term && term->history)
	{
		free(term->history->content);
		tmp = term->history;
		term->history = term->history->next;
		free(tmp);
		tmp = NULL;
	}
}

void		free_shell(t_core *shell)
{
	free_db(shell->env);
	free_prompt(shell);
	free_history(&shell->term);
	free_hash_map(&shell->hash);
}

void		free_lst(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (lst)
	{
		free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}
