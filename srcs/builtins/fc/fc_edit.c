/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/08 20:24:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

void	launch_editor(t_core *shell, t_cmd cmd)
{
	t_process	process;
	t_job		job;
	char		*command;

	ft_bzero(&process, sizeof(t_process));
	ft_bzero(&job, sizeof(t_job));
	command = ft_strjoin(cmd.editor, FC_TMP_FILE);
	process.av = ft_strsplit(command, SPACE);
	if (get_bin_path(shell, &process) != SUCCESS)
		ft_dprintf(STDERR_FILENO, "42sh: %s: not found\n", cmd.editor);
	call_bin(shell, &process);
	ft_strdel(&command);
	ft_tabdel(&process.av);
}

char	*get_editor(char **av, u_int64_t opt)
{
	char	*editor;

	editor = NULL;
	skip_options(&av);
	if (!*(av + 1) || (ft_isnum(*(av + 1)) && !(opt & (1ULL << 4))))
		editor = ft_strdup("ed ");
	else if (opt & (1ULL << 4))
		editor = ft_strjoin(*(av + 1), " ");
	return (editor);
}

int8_t	edit_mode(t_core *shell, t_process *process, u_int64_t opt)
{
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.editor = get_editor(process->av, opt);
	if ((cmd.fd = open(FC_TMP_FILE,
		(O_CREAT | O_WRONLY | O_APPEND), (S_IRUSR | S_IWUSR))) == FAILURE)
		return (fc_error(opt, 3));
	get_range(process->av, &cmd);
	launch_editor(shell, cmd);
	return (SUCCESS);
}
