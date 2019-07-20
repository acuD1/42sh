/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/20 17:32:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "shared_libft.h"
# include "define.h"
# include "struct.h"

# include <stdlib.h>

# include <stdio.h> // /!\ For debug only !

/*
**	Core
*/

void	print_opt(t_core *shell);

/*
**	DB
*/

void	init_shell(t_core *shell, char **environ);
int8_t	get_opt(int ac, char **av, t_core *shell);
int8_t	set_env(t_core *shell, char **environ);
t_db	*fetch_db(t_db *db, const char *s);

#endif
