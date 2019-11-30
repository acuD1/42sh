/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:51:01 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 16:49:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void ft_freejoblist(t_lst **lst)
{
	t_lst *tmp;
	t_lst *node;

	if (!lst)
		return;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			ft_free_processlist(&((t_job*)tmp->content)->process_list);
			free(((t_job*)tmp->content)->command);
			free((t_job*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break;
		}
		tmp = tmp->next;
		free(node);
	}
}

void ft_freetokenlist(t_lst **lst)
{
	t_lst *tmp;
	t_lst *node;

	if (!*lst)
		return;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free(((t_token*)tmp->content)->data);
			free((t_token*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break;
		}
		tmp = tmp->next;
		free(node);
	}
}

void ft_freedblist(t_lst **lst)
{
	t_lst *tmp;
	t_lst *node;

	if (!*lst)
		return;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free(((t_db*)tmp->content)->key);
			free(((t_db*)tmp->content)->value);
			free((t_db*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break;
		}
		tmp = tmp->next;
		free(node);
	}
}


void printjobbijobba(t_core *shell)
{
	if (shell->job_list)
	{
		ft_printjoblst(shell->job_list);
		// ft_freejoblist(&shell->job_list);
	}
	// if (shell->assign_list)
	// {
		// debug_ailleurs("/dev/ttys002", "============= ASSIGNATION LST ============\n");
		// ft_printassignlist(shell->assign_list);
		// ft_freedblist(&shell->assign_list);
	// }
}

void lexer_parser_analyzer(t_core *shell, char *line)
{
	t_lst *lxr_tok;
	t_lst *lst_job;

	lxr_tok = lexer(line);
	lst_job = NULL;
	shell->job_list = NULL;
	if (parser(lxr_tok) == TRUE)
	{
		shell->lexer = lxr_tok;
		analyzer(shell);
	//	ft_printjoblst(shell->job_list);
	}
	else
		ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n", ((t_token*)lxr_tok->content)->data);
}

