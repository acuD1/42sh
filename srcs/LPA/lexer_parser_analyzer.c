/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:51:01 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/19 17:52:35 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

#include <fcntl.h>

// int8_t		debug_ailleurs(const char *path, const char *str)
// {
// 	int8_t	fd;

// 	if ((fd = open(path, O_WRONLY)) < 0)
// 		return (FAILURE);
// 	dprintf(fd, "{%s}\n", str);
// 	return (SUCCESS);
// }

// int8_t		nono(const char *path)
// {
// 	int8_t	fd;

// 	if ((fd = open(path, O_WRONLY)) < 0)
// 		return (FAILURE);
// 	return (fd);
// }

// void		ft_printtab(char **cmd)
// {
// 	int		i;
// 	int8_t	j;

// 	i = 0;
// 	j = 0;
// 	if (cmd)
// 	{
// 		j = ft_tablen(cmd);
// 		dprintf(nono("/dev/ttys002"), "cmd {");
// 		while (cmd[i])
// 		{
// 			dprintf(nono("/dev/ttys002"), "'%s'", cmd[i]);
// 			i++;
// 		}
// 		dprintf(nono("/dev/ttys002"), "}\n");
// 	}
// }

// void			ft_printassignlist(t_lst *lst)
// {
// 	t_lst		*assign;
// 	int			x;

// 	x = 0;
// 	if (!lst)
// 		return ;
// 	assign = lst;
// 	while (assign)
// 	{
// 		debug_ailleurs("/dev/ttys002", "============= ASSIGN ============\n");
// 		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->key);
// 		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->value);
// 		assign = assign->next;
// 		x++;
// 	}
// }

// void			ft_printredir(t_redir *redir)
// {
// 	t_redir		*tmp;

// 	if (!redir)
// 		return ;
// 	tmp = redir;
// 	dprintf(nono("/dev/ttys002"), "redir state %u\n", tmp->type);
// 	if (tmp->op[0])
// 		dprintf(nono("/dev/ttys002"), "redir op[0] %s\n", tmp->op[0]);
// 	if (tmp->op[1])
// 		dprintf(nono("/dev/ttys002"), "redir op[1] %s\n", tmp->op[1]);
// 	if (tmp->type == P_DLESS)
// 		if (tmp->heredoc[0])
// 			dprintf(nono("/dev/ttys002"), "redir heredoc '%s`\n", tmp->heredoc);
// }

// void			ft_printprocess(t_process *process)
// {
// 	t_process	*tmp;
// 	t_token		*tok;
// 	t_lst		*ttp;

// 	if (!process)
// 		return ;
// 	tmp = process;
// 	dprintf(nono("/dev/ttys002"), "process state %u\n", tmp->type);
// 	dprintf(nono("/dev/ttys002"), "process command [%s]\n", tmp->command);
// 	if (tmp->av)
// 		ft_printtab(tmp->av);
// 	if (tmp->tok_list)
// 	{
// 		ttp = tmp->tok_list;
// 		while (ttp)
// 		{
// 			tok = ttp->content;
// 			dprintf(nono("/dev/ttys002"),
// 				"data /%s/ id %u \n", tok->data, tok->id);
// 			ttp = ttp->next;
// 		}
// 	}
// }

// void			ft_printjob(t_job *job)
// {
// 	t_job		*tmp;

// 	if (!job)
// 		return ;
// 	tmp = job;
// 	dprintf(nono("/dev/ttys002"), "job state %u\n", tmp->type);
// 	if (tmp->command)
// 		dprintf(nono("/dev/ttys002"), "job cmd {%s}\n", tmp->command);
// }

// void			ft_printjoblst(t_lst *list)
// {
// 	t_lst		*job;
// 	t_lst		*process;
// 	t_lst		*redir;

// 	if (!list)
// 		return ;
// 	job = list;
// 	while (job)
// 	{
// 		ft_printjob((t_job*)job->content);
// 		process = ((t_job*)job->content)->process_list;
// 		while (process)
// 		{
// 			ft_printprocess((t_process*)process->content);
// 			redir = ((t_process*)process->content)->redir_list;
// 			while (redir)
// 			{
// 				ft_printredir((t_redir*)redir->content);
// 				redir = redir->next;
// 			}
// 			ft_printassignlist(((t_process*)process->content)->assign_list);
// 			process = process->next;
// 		}
// 		job = job->next;
// 	}
// 	dprintf(nono("/dev/ttys002"), "\nLULU LA NANTAISE\n");
// }

void		ft_freejoblist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free_process_list(&((t_job*)tmp->content)->process_list);
			free(((t_job*)tmp->content)->command);
			free((t_job*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		free(node);
	}
	*lst = NULL;
}

void		ft_freetokenlist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			ft_strdel(&((t_token*)tmp->content)->data);
			free(tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		if (node)
			free(node);
	}
}

void		lexer_parser_analyzer(t_core *shell)
{
	t_lst	*lxr_tok;

	lxr_tok = lexer(shell->term.buffer);
	if (lxr_tok == NULL)
		return ;
	if (parser(lxr_tok) == TRUE)
		analyzer(shell, lxr_tok);
	ft_freetokenlist(&lxr_tok);
}
