/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/29 20:03:59 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		launch_editor(t_core *shell, t_process *process, t_cmd cmd)
{
	(void)shell;
	(void)process;
	cmd.editor = ft_strjoinf(cmd.editor, FC_TMP_FILE, 1);
	//ft_printf("%d\n", ft_strlen(cmd) + 1);
	//ft_printf("%s\n", cmd);
}

char		*get_editor(char **av, u_int64_t opt)
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

int8_t		edit_mode(t_core *shell, t_process *process, u_int64_t opt)
{
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.editor = get_editor(process->av, opt);
	if ((cmd.fd = open(FC_TMP_FILE, MODE_WRITE, S_USR_RW)) == FAILURE)
		return (fc_error(opt, 3));
	if (get_range(process->av, &cmd) == FALSE)
		return (fc_error(opt, 0));

//	ft_printtab(av);
	printf("[%s] [%d] [%d]\n", cmd.editor, cmd.first, cmd.last);



//	print_list(w, cmd, opt);

	launch_editor(shell, process, cmd);
	return (SUCCESS);
}
