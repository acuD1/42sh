/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:39 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:19:10 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_H
# define TWENTY_ONE_H

# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <stdlib.h>
# include <dirent.h>

# include "shared_libft.h"
# include "cmdline.h"
# include "builtins.h"

typedef struct		s_termcaps
{
	char			*cm;
	char			*ti;
}					t_termcaps;

typedef struct		s_sh
{
	struct termios	new_t;
	int				fd;
}					t_sh;

/*
** Initialization
*/
t_sh		*init_prompt(t_sh *term);
t_termcaps	*init_termcaps(void);
void		init_term(t_sh *data);
t_read		*get_size(t_read *data);

/*
** Execution
*/
int			exec_cmd(char **cmd, char ***env, t_read *line);

#endif
