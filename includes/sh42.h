/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/20 15:39:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "shared_libft.h"
# include "define.h"
# include "struct.h"
# include "command_line.h"
# include "enum.h"
# include "lexer_parser_analyzer.h"
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h> // /!\ For debug only !

/*
**	===========================================================================
**	CORE.......................................................................
**	===========================================================================
*/

int8_t		get_opt(int ac, char **av, t_core *shell);
void		credit(t_core *shell);

// char		*init_prompt(t_read *term);

void		print_opt(t_core *shell);
void		load_prompt(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell, char *line);
int8_t		dispatcher(t_core *shell, t_lst *jobs);

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

int32_t		exec_piped_process(t_core *shell, t_lst *process);
int8_t		call_builtin(t_core *shell, t_lst *process, int blt);
int8_t		exec_pipeline(t_core *shell, t_lst **process);
int8_t		exec_handler(t_core *shell, u_int8_t handler);
int8_t		exec_process(t_core *shell, t_lst *env);
int8_t		call_bin(t_core *shell, t_lst *process);
int8_t		task_master(t_core *shell);
int8_t		is_a_blt(char *cmd);
int8_t		get_bin(t_core *shell, t_process *process);
char		**set_envp(t_core *shell);
void		status_handler(t_core *shell, int status);

/*
**	===========================================================================
**	HASHMAP....................................................................
**	===========================================================================
*/

u_int32_t	get_hash(char *line, u_int32_t size);
int8_t		locate_hash(t_core *shell, t_lst *process);
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

t_core		*get_core(t_core *core);
int8_t		ft_access(char *path, int mode);
int8_t		is_a_dir(char *path);
void		print_usage(char *name, int c, char *usage);
void		ft_perror(const char *s, const int errnum);
char		*get_abs_path(char *path);
int			check_invalid_identifiers(char *arg, char *exceptions);

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

int8_t		builtin_set(t_core *shell, t_process *process);
int8_t		builtin_unset(t_core *shell, t_process *process);
int8_t		builtin_export(t_core *shell, t_process *process);
int8_t		builtin_fc(t_core *shell, t_process *process);

/*
**	===========================================================================
**	REDIRECTIONS...............................................................
**	===========================================================================
*/

int8_t			exec_redirs(t_lst *redirs);
int8_t			dup_output(int fd, t_redir *ptr);
int8_t			dup_input(int fd, t_redir *ptr);
int8_t			append_output(t_redir *ptr);
int8_t			redir_output(t_redir *ptr);
int8_t			redir_input(t_redir *ptr);
int8_t			dup_ifd(t_redir *ptr);
int8_t			dup_ofd(t_redir *ptr);
void			close_fds(t_lst *ptr);

/* ###########################  TEMPORARY   #################################*/
void	debug_analyzer(t_core *shell);

#endif
