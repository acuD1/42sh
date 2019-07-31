/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/27 14:53:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "shared_libft.h"
# include "define.h"
# include "struct.h"
# include "lexer.h"

# include <stdlib.h>
# include <unistd.h>
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

void		exec_process(t_core *shell, t_lst *env);
void		exec_handler(t_core *shell, u_int8_t handler);
char		*get_bin(t_core *shell, t_lst *env);
char		**set_envp(t_core *shell);

/*
**	DEV
*/

void		print_tokens(t_core *shell);
void		print_env(t_core *shell);


/*
** Lexer
*/

void	lexer(t_core *shell, char *line);

#endif
