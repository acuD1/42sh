/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 18:09:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		launch_editor(t_core *shell, char *ed, char *cmd)
{
	ft_printf("%d\n", ft_strlen(cmd) + 1);
	ft_strcpy(shell->input->buffer, ed);
	lexer_parser_analyzer(shell, ed);
	if (task_master(shell) != SUCCESS)
		exit(1);


	ft_printf("%s\n", cmd);
	lexer_parser_analyzer(shell, cmd);
	if (task_master(shell) != SUCCESS)
		exit(1);
}

int8_t		edit_mode(t_core *shell, t_lst *w, u_int64_t opt, char **range)
{
	char	ed[BUFF_SIZE];

	ft_bzero(ed, BUFF_SIZE);
	ft_strcpy(ed, "ed");
	if (opt & (1ULL << 4))
	{
		if (range[0])
		{
			ft_bzero(ed, BUFF_SIZE);
			ft_strcpy(ed, range[0]);
		}
		else
		{
			print_usage("fc", 0, "fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
			return (FAILURE);
		}
	}
	else if (range[0])
		set_range(&w, range);
	launch_editor(shell, ed, w->content);
	return (SUCCESS);
}
