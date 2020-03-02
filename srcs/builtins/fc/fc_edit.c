/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/02 15:58:09 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

static int8_t	fc_exec_cmd(t_core *shell, t_cmd cmd)
{
	while (ft_getnextline(cmd.fd, &shell->term.buffer) > 0)
	{
		lexer_parser_analyzer(shell);
		do_job_notification(shell, shell->launched_jobs);
		if (task_master(shell) != SUCCESS)
		{
			close(cmd.fd);
			return (FAILURE);
		}
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
	}
	close(cmd.fd);
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_memalloc(BUFF_SIZE);
	return (SUCCESS);
}

static int8_t	fc_editor(t_core *shell, t_cmd cmd)
{
	char		*command;

	command = ft_strjoin(cmd.editor, FC_TMP_FILE);
	if ((cmd.fd = open(FC_TMP_FILE, O_RDONLY,
									S_IRUSR | S_IRGRP | S_IROTH)) == -1)
		return (FAILURE);
	if (fc_launch_editor(shell, ft_strsplit(command, SPACE)) == FAILURE)
		return (FAILURE);
	ft_strdel(&command);
	ft_strdel(&shell->term.buffer);
	if (fc_exec_cmd(shell, cmd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

char			*get_editor(char **av, u_int64_t opt)
{
	char		*editor;

	editor = NULL;
	skip_options(&av);
	if (!*(av + 1) || (ft_isnum(*(av + 1)) && !(opt & (1ULL << 4))))
		editor = ft_strdup("ed ");
	else if (opt & (1ULL << 4))
		editor = ft_strjoin(*(av + 1), " ");
	return (editor);
}

int8_t			edit_mode(t_core *shell, t_process *process, u_int64_t opt)
{
	t_cmd		cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.editor = get_editor(process->av, opt);
	if ((cmd.fd = open(FC_TMP_FILE,
		(O_CREAT | O_WRONLY | O_TRUNC), (S_IRUSR | S_IWUSR))) == FAILURE)
		return (fc_error(opt, 4));
	if (ft_tablen(process->av) > 1 && get_range(process->av, &cmd) == FALSE)
		return (fc_error(opt, 0));
	get_entries(shell->term.history, &cmd, opt);
	sort_print_cmd(cmd, shell->term.history, opt);
	return (fc_editor(shell, cmd));
}
