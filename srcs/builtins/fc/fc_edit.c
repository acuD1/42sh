/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/21 12:47:15 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

static int8_t	fc_exec_cmd(t_core *shell, t_cmd cmd)
{
	while (ft_getnextline(cmd.fd, &shell->term.buffer) > 0)
	{
		ft_dprintf(STDIN_FILENO, "%s\n", shell->term.buffer);
		lexer_parser_analyzer(shell);
		do_job_notification(shell, shell->launched_jobs, TRUE);
		task_master(shell);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
	}
	close(cmd.fd);
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
	ft_strdel(&cmd.editor);
	return (SUCCESS);
}

static int8_t	fc_editor(t_core *shell, t_cmd cmd)
{
	char		*command;

	command = ft_strjoin(cmd.editor, FC_TMP_FILE);
	if ((cmd.fd = open(FC_TMP_FILE, O_RDONLY,
									S_IRUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_strdel(&command);
		ft_strdel(&cmd.editor);
		return (FAILURE);
	}
	if (fc_launch_editor(shell, ft_strsplit(command, SPACE)) == FAILURE)
	{
		ft_strdel(&command);
		ft_strdel(&cmd.editor);
		return (FAILURE);
	}
	ft_strdel(&command);
	ft_strdel(&shell->term.buffer);
	if (fc_exec_cmd(shell, cmd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static char		*get_editor(t_core *shell, char **av, u_int64_t opt)
{
	char		*editor;

	editor = NULL;
	if (!opt || ft_isnum(*(av + 1)))
	{
		get_edit_value(shell, "FCEDIT", &editor);
		return (editor);
	}
	else if (opt & (1ULL << 4) && ft_tablen(av) == 2)
		return (NULL);
	av++;
	if (*(av + 1) == NULL)
		return (NULL);
	if (ft_strequ(*av, "-e") == TRUE)
	{
		(av)++;
		editor = ft_strjoin(*av, " ");
	}
	else
		editor = ft_strjoin(*(av + 1), " ");
	return (editor);
}

static void		get_edit_entries(t_lst *w, t_cmd *cmd)
{
	int32_t		w_entries;

	w_entries = (int32_t)ft_lstlen(w);
	if (cmd->ac == 1 || cmd->ac == 3)
	{
		cmd->first = w_entries;
		cmd->last = w_entries;
	}
	else if (cmd->ac == 2)
		cmd->last = cmd->first;
	else if (cmd->ac == 4)
		cmd->last = cmd->first;
	if (cmd->first <= 0)
		cmd->first = w_entries + cmd->first;
	if (cmd->last <= 0)
		cmd->last = w_entries + cmd->last;
}

int8_t			edit_mode(t_core *shell, t_process *process, u_int64_t opt)
{
	t_cmd		cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	if ((cmd.fd = open(FC_TMP_FILE,
		(O_CREAT | O_WRONLY | O_TRUNC), (S_IRUSR | S_IWUSR))) == FAILURE)
		return (fc_error(opt, 4));
	if (!shell->term.history)
		return (fc_error(opt, 0));
	cmd.ac = ft_tablen(process->av);
	get_range(process->av, &cmd, opt);
	get_edit_entries(shell->term.history, &cmd);
	sort_print_cmd(cmd, shell->term.history, opt);
	if ((cmd.editor = get_editor(shell, process->av, opt)) == NULL)
		return (fc_error(opt, 2));
	return (fc_editor(shell, cmd));
}
