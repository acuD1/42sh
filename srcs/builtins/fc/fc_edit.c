/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/28 20:19:48 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		launch_editor(t_core *shell, char *ed, char *cmd)
{
	(void)ed;
	(void)shell;
	ft_printf("%d\n", ft_strlen(cmd) + 1);
	//lexer_parser_analyzer(shell);
	//if (task_master(shell) != SUCCESS)
	//	exit(1);
	//ft_printf("%s\n", cmd);
}

char		*get_editor(char **av, u_int64_t opt)
{
	char	*editor;

	editor = NULL;
	if (!*av || ft_isnum(*av))
		editor = ft_strdup("ed ");
	else if (opt & (1ULL << 4))
		editor = ft_strjoin(*av, " ");
	return (editor);
}

int8_t		edit_mode(t_core *shell, t_lst *w, char **av, u_int64_t opt)
{
	t_cmd	cmd;
	char	*editor;

	(void)shell;
	(void)w;
	ft_bzero(&cmd, sizeof(t_cmd));
	get_range(av, &cmd);
	if (opt & (1ULL << 4) && cmd.ac == 2)
		return (fc_error(opt, 2));
	else
		editor = get_editor(av + 1, opt);
	editor = ft_strjoinf(editor, FC_TMP_FILE, 1);

	if ((cmd.fd = open(FC_TMP_FILE, MODE_WRITE, S_USR_RW | S_GRP_OTH_R)) == FAILURE)
		return (fc_error(opt, 3));

	ft_printtab(av);
	printf("[%s] [%d] [%d]\n", editor, cmd.first, cmd.last);


	print_list(w, cmd, opt);

	launch_editor(shell, editor, w->content);
	return (SUCCESS);
}
