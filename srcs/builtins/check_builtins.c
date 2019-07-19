/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:43 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/18 16:50:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/twenty_one.h"

int	check_builtins(char **cmd, char **env, t_read *term)
{
	if (!ft_strcmp(term->buffer, "exit"))
		return (exit_sh(term));
	else if (!ft_strcmp(cmd[0], "history"))
		return (history(term, cmd));
	return (0);
}
