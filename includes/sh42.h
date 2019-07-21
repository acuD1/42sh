/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/21 14:11:03 by arsciand         ###   ########.fr       */
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

void		credit(t_core *shell);
void		init_prompt(void);
void		print_opt(t_core *shell);
void		load_prompt(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell, char *line);

/*
**	DB
*/

void		init_shell(t_core *shell);
int8_t		get_opt(int ac, char **av, t_core *shell);
int8_t		set_env(t_core *shell, char **environ);
t_db		*fetch_db(t_db *db, const char *s);
int8_t		get_tokens(t_core *shell, char *line);

/*
**	Exec
*/


/*
**	DEV
*/

void		print_tokens(t_core *shell);
void		print_env(t_core *shell);

#endif