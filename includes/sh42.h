/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/03 16:21:13 by arsciand         ###   ########.fr       */
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

/*
**	DEBUG
*/

# include <stdio.h>
# include <setjmp.h>

jmp_buf g_exit_leaks;

/*
**	===========================================================================
**	CORE.......................................................................
**	===========================================================================
*/

void		get_opt(int ac, char **av, t_core *shell);
void		version(t_core *shell);
void		load_i_mode(t_core *shell);
void		load_noi_mode(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell);
//void		free_history(t_read *term);
void		free_shell(t_core *shell);
void		reset_hash(t_hash *hash);
//int8_t		dispatcher(t_core *shell, t_lst *jobs);

/*
**	===========================================================================
**	DB.........................................................................
**	===========================================================================
*/

int8_t		set_env(t_core *shell, char **argv, char **environ);
int8_t		del_db(t_core *shell, char *key);
int8_t		init_shell(t_core *shell, char **av, char **environ);
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

int8_t		call_builtin(t_core *shell, t_process *process, int blt);
//int8_t		exec_handler(t_core *shell, u_int8_t handler);
int8_t		get_bin_path(t_core *shell, t_process *process);
void		exec_process
				(t_core *shell, t_job *job, t_process *process, int *fds);
int8_t		call_bin(t_core *shell, t_process *process);
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
void		hash_map_dispatcher
				(t_core *shell, t_process *process, enum e_hash fmt);
int8_t		resize_hash_map(t_core *shell);
void		free_hash_map(t_hash *hash);
t_db		*fetch_hash_db
				(t_db *db, const char *key, const char *value, enum e_hash fmt);
void		hash_key_remover(t_core *shell, char *process);
int8_t		hash_l(t_core *shell, t_process *process, int ac);
int8_t		hash_r(t_core *shell, t_process *process, int ac);
int8_t		hash_p(t_core *shell, t_process *process, int ac);
int8_t		hash_d(t_core *shell, t_process *process, int ac);
int8_t		hash_t(t_core *shell, t_process *process, int ac);
void		print_hash_map(t_core *shell, enum e_hash fmt);
void		find_hash(t_core *shell, t_process *process, int ac);
void		free_hash_key(t_hash *hash, t_lst *map);
void		hash_error(t_hash *hash);

/*
**	===========================================================================
**	DEV........................................................................
**	===========================================================================
*/

//void		print_env(t_core *shell);
//void		print_hash_map_dev(t_hash *hash);

/*
**	===========================================================================
**	MISC.......................................................................
**	===========================================================================
*/

t_core		*get_core(t_core *core);
//int			check_invalid_identifiers(char *arg, char *exceptions);
int8_t		get_canonical_path(char *path, char *buffer);
void		ft_perror(const char *s, const char *name, const int errnum);
int8_t		ft_access(char *path, int mode);
int8_t		is_a_dir(char *path);
void		print_usage(char *name, int c, char *usage);
void		quit_shell(t_core *shell, int exit_value, int8_t v);
void		print_and_quit(t_core *shell, char *message);
int			check_invalid_identifiers(char *arg, char *exceptions);
char		*signal_msg(int sig);
//void		debug_job(t_job *job);

/*
**	===========================================================================
**	SHELL VARIABLE UPDATES/CREATIONS...........................................
**	===========================================================================
*/

int8_t		increment_shlvl(t_core *shell);
int8_t		update_pwd(t_core *shell);
//int8_t		update_(t_core *shell);
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
//int8_t		update_backgroud_pid(t_core *shell);
int8_t		update_last_arg(t_core *shell, char **argv);
int8_t		update_oldpwd(t_core *shell, char *oldpwd);

/*
**	===========================================================================
**	BUILTINS...................................................................
**	===========================================================================
*/

int8_t		builtin_set(t_core *shell, t_process *process);
int8_t		builtin_unset(t_core *shell, t_process *process);
int8_t		builtin_export(t_core *shell, t_process *process);
int8_t		builtin_exit(t_core *shell, t_process *process);
int8_t		builtin_hash(t_core *shell, t_process *process);
int8_t		builtin_cd(t_core *shell, t_process *process);
int8_t		builtin_echo(t_core *shell, t_process *process);
int8_t		builtin_pwd(t_core *shell, t_process *process);
int8_t		builtin_type(t_core *shell, t_process *process);
int8_t		builtin_fg(t_core *shell, t_process *process);
int8_t		builtin_jobs(t_core *shell, t_process *process);
int8_t		builtin_bg(t_core *shell, t_process *process);
//int8_t		edit_mode(t_core *shell, t_lst *w, u_int64_t opt, char **range);
//void		listing_mode(t_lst *saved, u_int64_t opt, char **range);
//void		display_reverse(t_lst *w, u_int64_t opt, char **range);
//u_int8_t	select_specifier(t_core *shell, t_lst *w, char **cmd);
//void		swap_range(char **r1, char **r2);
//u_int16_t	set_range(t_lst **w, char **range);

/*
**	===========================================================================
**	REDIRECTIONS...............................................................
**	===========================================================================
*/

int8_t		exec_redirs(t_core *shell, t_lst *redirs);
int8_t		dup_output(int fd, t_redir *ptr);
int8_t		dup_input(int fd, t_redir *ptr);
int8_t		append_output(t_redir *ptr);
int8_t		redir_output(t_redir *ptr);
int8_t		redir_input(t_redir *ptr);
int8_t		dup_ifd(t_redir *ptr);
int8_t		dup_ofd(t_redir *ptr);
void		close_fds(t_lst *ptr);
int8_t		write_heredoc(t_redir *ptr);

/*
**	===========================================================================
**	SIGNALS....................................................................
**	===========================================================================
*/

//void		kill_processes(int signum, t_core *shell);
void		sigint_handler(int sig_num);
void		init_signals(void);

/*
** TMP
*/

/*
**	===========================================================================
**	JOB CONTROL................................................................
**	===========================================================================
*/

//t_job		*find_job(t_lst *ptr, pid_t pgid);
t_process	*find_process(t_lst *job, pid_t pid);
int8_t		job_is_stopped(t_job *job);
int8_t		job_is_completed(t_job *job);
int8_t		put_job_in_foreground
				(t_core *shell, t_lst *jobs, t_job *job, int cont);
void		put_job_in_background(t_core *shell, t_job *job, int cont);
//void		mark_job_as_running(t_job *job);
int8_t		continue_job(t_core *shell, t_job *job, int foreground);
void		reset_signals(void);
void		launch_process
				(t_core *shell, t_process *process, int infile, int outfile);
void		launch_job(t_core *shell, t_job *job, int foreground);
//int8_t		do_job_notification(t_core *shell, t_lst *job);
void		job_background_notif(t_job *job);
void		wait_for_job(t_core *shell, t_lst *jobs, t_job *job);
int8_t		mark_process_status
				(t_core *shell, t_lst *jobs, pid_t pid, int status);
int8_t		launch_blt
				(t_core *shell, t_process *process, int *fds, int foreground);
void		wait_for_process(t_core *shell, t_lst *jobs, t_process *process);
void		update_status(t_core *shell);
t_job		*get_job(t_lst *jobs, char *str);
t_job		*get_job_by_id(t_lst *jobs, int id);
void		format_job_info(t_job *job);
int			update_jobs(t_lst *jobs);
void		attr_jobc_id(t_core *shell, t_job *job);

//void		debug_analyzer(t_core *shell);

#endif
