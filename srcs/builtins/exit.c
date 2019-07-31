/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:16 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/09 17:36:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/twenty_one.h"

void			reset_term()
{
	struct termios	old_t;

	tcgetattr(0, &old_t);
	old_t.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &old_t);
}

int			exit_sh(t_read *term)
{
	reset_term();
	free(term->prompt);
	free(term->line);
	exit(0);
	return (0);
}
