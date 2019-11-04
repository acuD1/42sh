/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/04 14:31:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "shared_libft.h"
# include "define.h"
# include "struct.h"
# include "command_line.h"

# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h> // /!\ For debug only !

/*
**	===========================================================================
**	CORE.......................................................................
**	===========================================================================
*/

int8_t		get_opt(int ac, char **av, t_core *shell);
void		credit(t_core *shell);

//void		init_prompt(void);

void		print_opt(t_core *shell);
void		load_prompt(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell, char *line);

/*
**	===========================================================================
**	DB.........................................................................
**	===========================================================================
*/

int8_t		set_env(t_core *shell, char **argv, char **environ);
int8_t		get_tokens(t_core *shell, char *line);
int8_t		del_db(t_core *shell, char *key);
void		init_shell(t_core *shell);
t_db		*fetch_db(t_db *db, const char *s, const u_int8_t var_type);
t_db		*modify_db(t_db	*db, char *new_value, u_int8_t new_type);
t_db		*get_or_create_db(t_core *shell, char *key, u_int8_t var_type);
t_db		*search_db(t_lst *env, char *key);
int8_t		edit_var(t_core *shell, char *name, char *value, u_int8_t var_type);

/*
**	===========================================================================
**	EXEC.......................................................................
**	===========================================================================
*/

void		exec_process(t_core *shell, t_lst *env);
void		exec_handler(t_core *shell, u_int8_t handler);
char		*get_bin(t_core *shell, t_lst *env);
char		**set_envp(t_core *shell);

/*
**	===========================================================================
**	HASHMAP....................................................................
**	===========================================================================
*/

u_int32_t	get_hash(char *line, u_int32_t size);
int8_t		locate_hash(t_core *shell, t_hash *hash);
int8_t		add_hash_map(t_core *shell, t_hash *hash);
int8_t		resize_hash_map(t_core *shell, t_hash *hash);
void		free_hash_map(t_hash *hash);
t_db		*fetch_hash_db(t_db *db, const char *key, const char *value);

/*
**	===========================================================================
**	DEV........................................................................
**	===========================================================================
*/

void		print_tokens(t_core *shell);
void		print_env(t_core *shell);
void		print_hash_map(t_hash *hash);

/*
**	===========================================================================
**	MISC.......................................................................
**	===========================================================================
*/

void		print_usage(char *name, int c, char *usage);
t_core		*get_core(t_core *core);
int		check_invalid_identifiers(char *arg, char *exceptions);
char		*get_abs_path(char *path);
void		ft_perror(const char *s, const int errnum);
int8_t		ft_access(char *path, int mode);

/*
**	===========================================================================
**	SHELL VARIABLE UPDATES/CREATIONS...........................................
**	===========================================================================
*/

int8_t		increment_shlvl(t_core *shell);
int8_t		update_pwd(t_core *shell);
int8_t		update_(t_core *shell);
int8_t		update_ifs(t_core *shell);
int8_t		update_termsize(t_core *shell);
int8_t		create_term(t_core *shell);
int8_t		update_histfile(t_core *shell);
int8_t		update_hist_size(t_core *shell);
int8_t		update_histfile_size(t_core *shell);
int8_t		update_version(t_core *shell);
int8_t		update_sharp_var(t_core *shell);
int8_t		update_process_id(t_core *shell);
int8_t		update_shell_name(t_core *shell);
int8_t		update_shell_flags(t_core *shell);
int8_t		update_exit_status(t_core *shell);
int8_t		update_backgroud_pid(t_core *shell);
int8_t		update_last_arg(t_core *shell, char **argv);

/*
**	===========================================================================
**	BUILTINS...................................................................
**	===========================================================================
*/

int8_t		builtin_set(t_core *shell);
int8_t		builtin_unset(t_core *shell);
int8_t		builtin_export(t_core *shell);
int8_t		builtin_fc(t_core *shell);
int8_t		edit_mode(t_core *shell, t_lst *w, u_int64_t opt, char **range);
void		display_reverse(t_lst *w, u_int64_t opt, char **range);
u_int16_t	set_range(t_lst **w, char **range);
void		swap_range(char **r1, char **r2);
void		sort_rrange(t_lst *w, int *ret, size_t *num, char **range);

/* ###########################  TEMPORARY   #################################*/
int8_t		exec_builtin(t_core *shell);

#endif
