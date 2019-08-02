/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:28 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 14:25:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdio.h>
# include "twenty_one.h"

int			main(int ac, char **av, char **env)
{
	t_read		term;
	t_sh		*sh;
	t_termcaps	*caps;
	char		buf[2048];
	char		**tab_cpy;
	char		**cmd;

	sh = NULL;
	sh = ft_memalloc(sizeof(sh));
	//init_term(sh);
	caps = init_termcaps();
	tab_cpy = ft_tabcopy(tab_cpy, env);
	term.history = NULL;
	term.history_index = NULL;
	while (1)
	{
		display_prompt(&term);
		ft_bzero(term.buffer, term.width);
		while (read(0, buf, 2048) > 0)
			if (!check_caps(buf, &term))
				break ;
			else
				continue ;
		cmd = ft_split(term.buffer);
		term.ac = ft_tablen(cmd);
		*cmd ? exec_cmd(cmd, &tab_cpy, &term) : 0;
		save_history(&term);
		ft_tabfree(cmd);
	}
}
