/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:38:43 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/19 20:18:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "twenty_one.h"

/*
** Bultins Handler
*/
int	check_builtins(char **cmd, char **env, t_read *term);

/*
** Builtins
*/
int	exit_sh(t_read *term);
int	history(t_read *term, char **cmd);

#endif
