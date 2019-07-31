/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:07 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:05:13 by fcatusse         ###   ########.fr       */
/*   Updated: 2019/07/23 11:04:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"
# include <sys/ioctl.h>

void				init_term(t_sh *data)
{
	struct termios		old_t;
	struct termios		new_t;

	tgetent(NULL, "xterm-256color");
	if (tcgetattr(0, &old_t) == -1)
		return ;
	if (ioctl(0, TIOCGETA, &old_t) < 0)
		return ;
	new_t = old_t;
	new_t.c_lflag &= ~(ICANON | ECHO);
	new_t.c_cc[VMIN] = 1;
	new_t.c_cc[VTIME] = 0;
	if (ioctl(0, TIOCSETA, &old_t) < 0)
		return ;
	if (tcsetattr(0, TCSANOW, &new_t) == -1)
		return ;
}
