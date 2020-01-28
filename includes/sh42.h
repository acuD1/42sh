/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/28 19:52:39 by fcatusse         ###   ########.fr       */
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
# include "expansion.h"
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h> // /!\ For debug only !
# include <setjmp.h>

jmp_buf exit_leaks;

/*
**	===========================================================================
**	CORE.......................................................................
**	===========================================================================
*/

int8_t		get_opt(int ac, char **av, t_core *shell);
void		credit(t_core *shell);

void		print_opt(t_core *shell);
void		load_prompt(t_core *shell);
void		load_noi_mode(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell);
void		free_history(t_read *term);
int8_t		dispatcher(t_core *shell, t_lst *jobs);

/*
**	===========================================================================
**	DB.........................................................................
**	===========================================================================
*/

int8_t		set_env(t_core *shell, char **argv, char **environ);
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
int8_t		locate_hash(t_core *shell, t_process *process);
int8_t		hash_map_dispatcher
	(t_core *shell, t_process *process, u_int8_t format);
int8_t		resize_hash_map(t_core *shell);
void		free_hash_map(t_hash *hash);
t_db		*fetch_hash_db
	(t_db *db, const char *key, const char *value, u_int8_t format);
void 		del_hash_key(t_core *shell, char *process);

/*
**	===========================================================================
**	DEV........................................................................
**	===========================================================================
*/

void		print_env(t_core *shell);
void		print_hash_map_dev(t_hash *hash);

/*
**	===========================================================================
**	MISC.......................................................................
**	===========================================================================
*/

t_core		*get_core(t_core *core);
int			check_invalid_identifiers(char *arg, char *exceptions);
int8_t		get_canonical_path(char *path, char *buffer);
void		ft_perror(const char *s, const char *name, const int errnum);
int8_t		ft_access(char *path, int mode);
int8_t		is_a_dir(char *path);
void		print_usage(char *name, int c, char *usage);
void		quit_shell(t_core *shell, int exit_value, int8_t verbose);
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
int8_t		builtin_exit(t_core *shell, t_process *process);
int8_t		builtin_hash(t_core *shell, t_process *process);
int8_t		builtin_cd(t_core *shell, t_process *process);
int8_t		builtin_echo(t_core *shell, t_process *process);
int8_t		builtin_pwd(t_core *shell, t_process *process);

int8_t		edit_mode(t_core *shell, t_lst *w, char **av, u_int64_t opt);
int8_t		listing_mode(t_lst *w, char **av, u_int64_t opt);
int8_t		select_specifier(t_core *shell, t_lst *w, char **av);
int8_t		fc_error(u_int64_t opt, int err_num);
u_int8_t	get_range(char **av, t_cmd *cmd);
void		get_entries(t_lst *w, t_cmd *cmd);
void		print_list(t_lst *w, t_cmd cmd, u_int64_t opt);
void		print_reverse(t_lst *w, t_cmd cmd, u_int64_t opt);
void		skip_options(char ***av);

/*
**	===========================================================================
**	REDIRECTIONS...............................................................
**	===========================================================================
*/

int8_t			exec_redirs(t_core *shell, t_lst *redirs);
int8_t			dup_output(int fd, t_redir *ptr);
int8_t			dup_input(int fd, t_redir *ptr);
int8_t			append_output(t_redir *ptr);
int8_t			redir_output(t_redir *ptr);
int8_t			redir_input(t_redir *ptr);
int8_t			dup_ifd(t_redir *ptr);
int8_t			dup_ofd(t_redir *ptr);
void			close_fds(t_lst *ptr);
int8_t			write_heredoc(t_redir *ptr);

/*
**	===========================================================================
**	SIGNALS....................................................................
**	===========================================================================
*/

void	kill_processes(int signum, t_core *shell);
void	sigint_handler(int sig_num);
void	init_signals(void);

/* ###########################  TEMPORARY   #################################*/
void	debug_analyzer(t_core *shell);

#endif
