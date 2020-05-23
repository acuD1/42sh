/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:27:32 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/07 15:13:53 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

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
	free_db(shell->pos_vars);
	free_prompt(shell);
	free_history(&shell->term);
	free_hash_map(&shell->hash);
	ft_freejoblist(&shell->job_list);
	ft_freejoblist(&shell->launched_jobs);
}

void		free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}
