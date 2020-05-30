/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/20 14:05:38 by fcatusse         ###   ########.fr       */
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

/*
**	DEBUG
*/

# include <setjmp.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

extern jmp_buf g_exit_leaks;

void		set_termconfig(t_core *shell);

/*
**	===========================================================================
**	CORE.......................................................................
**	===========================================================================
*/

void		get_opt(int ac, char **av, t_core *shell);
void		version(t_core *shell);
void		load_i_mode(t_core *shell);
void		load_noi_mode(t_core *shell);
void		free_db(t_lst *env);
void		free_prompt(t_core *shell);
void		free_shell(t_core *shell);
void		reset_hash(t_hash *hash);

/*
**	===========================================================================
**	DB.........................................................................
**	===========================================================================
*/

int8_t		set_env(t_core *shell, char **argv, char **environ);
int8_t		del_db(t_core *shell, const char *key);
int8_t		init_shell(t_core *shell, char **av, char **environ);
t_db		*fetch_db(t_db *db, const char *s, u_int8_t v_type);
t_db		*modify_db(t_db	*db, char *new_value, u_int8_t new_type);
t_db		*get_or_create_db(t_core *shell, const char *key, u_int8_t v_type);
t_db		*search_db(t_lst *env, const char *key);
int8_t		edit_var
				(t_core *shell, const char *name, char *value, u_int8_t v_type);

/*
**	===========================================================================
**	EXEC.......................................................................
**	===========================================================================
*/

int8_t		call_builtin(t_core *shell, t_process *process, int8_t blt);
int8_t		get_bin_path(t_core *shell, t_process *process);
void		exec_process(t_core *shell, t_job *job, t_process *process);
void		call_bin(t_core *shell, t_process *process);
void		task_master(t_core *shell);
int8_t		is_a_blt(const char *cmd);
int8_t		get_bin(t_core *shell, t_process *process);
char		**set_envp(t_core *shell);
void		status_handler(t_core *shell, t_process *process);

/*
**	===========================================================================
**	HASHMAP....................................................................
**	===========================================================================
*/

u_int32_t	get_hash(const char *line, u_int32_t size);
int8_t		locate_hash(t_core *shell, t_process *process);
void		hash_dispatcher
				(t_core *shell, t_process *process, enum e_hash fmt);
int8_t		fill_exec
				(t_core *shell, const char *key,
				const char *value, enum e_hash fmt);
int8_t		fill_path
				(t_core *shell, t_process *process, enum e_hash fmt, size_t i);
int8_t		fill_default
				(t_core *shell, t_process *process, enum e_hash fmt, size_t i);
int8_t		resize_hash_map(t_core *shell);
void		free_hash_map(t_hash *hash);
t_db		*fetch_hash_db
				(t_db *db, const char *key, const char *value, enum e_hash fmt);
void		hash_key_remover(t_core *shell, char *process);
int8_t		hash_l(t_core *shell, t_process *process, size_t ac);
int8_t		hash_r(t_core *shell, t_process *process, size_t ac);
int8_t		hash_p(t_core *shell, t_process *process, size_t ac);
int8_t		hash_d(t_core *shell, t_process *process, size_t ac);
int8_t		hash_t(t_core *shell, t_process *process, size_t ac);
void		print_hash_map(t_core *shell, enum e_hash fmt);
void		find_hash(t_core *shell, t_process *process, size_t ac);
void		free_hash_key(t_hash *hash, t_lst *map);
void		hash_error(t_hash *hash);

/*
**	===========================================================================
**	MISC.......................................................................
**	===========================================================================
*/

void		free_process_link(t_lst *ptr);
int			get_signal(int status);
t_core		*get_core(t_core *core);
int8_t		get_canonical_path
	(t_core *shell, const char *path, char *buffer, char *pwd);
void		ft_perror(const char *s, const char *name, int8_t errnum);
int8_t		ft_access(const char *path, u_int8_t mode);
int8_t		is_a_dir(const char *path);
void		print_usage(const char *name, u_int8_t c, const char *usage);
void		quit_shell(t_core *shell, int exit_value, int8_t v);
void		print_and_quit(t_core *shell, const char *message);
int8_t		check_invalid_identifiers(const char *arg, const char *exceptions);
char		*signal_msg(int sig);
int8_t		path_tests(const char *path, int opt);
void		dir_backward(char *path);
int8_t		dir_forward(char *path);
int8_t		dir_write(const char *rel, char *abs);
int8_t		check_filename_length(const char *str);
void		print_n(t_read *term);

/*
**	===========================================================================
**	SHELL VARIABLE UPDATES/CREATIONS...........................................
**	===========================================================================
*/

int8_t		increment_shlvl(t_core *shell);
int8_t		update_pwd(t_core *shell);
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
int8_t		update_background_pid(t_core *shell);
int8_t		update_ps1(t_core *shell);
int8_t		update_ps2(t_core *shell);
int8_t		update_last_arg(t_core *shell, char **argv);
int8_t		update_oldpwd(t_core *shell);

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
int8_t		builtin_fc(t_core *shell, t_process *process);
int8_t		builtin_test(t_core *shell, t_process *process);
int8_t		edit_mode(t_core *shell, t_process *process, u_int64_t opt);
int8_t		listing_mode(t_lst *w, char **av, u_int64_t opt);
int8_t		select_specifier(t_core *shell, char **av);
int8_t		fc_error(u_int64_t opt, int err_num);
int8_t		get_range(char **av, t_cmd *cmd, u_int64_t opt);
void		get_entries(t_lst *w, t_cmd *cmd, u_int64_t opt);
void		print_list(t_lst *w, t_cmd cmd, u_int64_t opt);
void		print_reverse(t_lst *w, t_cmd cmd, u_int64_t opt);
void		skip_options(char ***av);
void		sort_print_cmd(t_cmd cmd, t_lst *w, u_int64_t opt);
void		print_and_exec(t_core *shell, int fd);
void		get_edit_value(t_core *shell, const char *key, char **editor);
int32_t		check_pattern(char *pat);
int32_t		search_pattern(char *pat, int8_t i);
int8_t		fc_launch_editor(t_core *shell, char **av);
int8_t		cd_update_pwd(t_core *shell, const char *pwd, const char *path);
int8_t		cd_check_path(const char *path);
int8_t		change_dir(t_core *shell, const char *path);
int8_t		update_pwds(t_core *shell, const char *buffer, const char *path);
int8_t		cd_use_cd_path(t_core *shell, const char *path);
int8_t		cd_oldpwd(t_core *shell);
int8_t		cd_home(t_core *shell);

/*
**	===========================================================================
**	REDIRECTIONS...............................................................
**	===========================================================================
*/

int8_t		exec_redirs(t_core *shell, t_process *process, t_lst *redirs);
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

void		sigint_special_handler(void);
void		sigint_handler(int sig_num);
void		init_signals(void);
void		send_hup(t_core *shell);

/*
**	===========================================================================
**	JOB CONTROL................................................................
**	===========================================================================
*/

t_process	*find_process(t_lst *job, pid_t pid);
u_int8_t	job_is_stopped(t_job *job);
u_int8_t	job_is_completed(t_job *job);
void		put_job_in_foreground
				(t_core *shell, t_lst *jobs, t_job *job, u_int8_t cont);
void		put_job_in_background(t_core *shell, t_job *job, u_int8_t cont);
void		continue_job(t_core *shell, t_job *job, int foreground);
void		reset_signals(void);
void		launch_process(t_core *shell, t_process *process);
int8_t		launch_job(t_core *shell, t_job *job, int foreground);
void		job_background_notif(t_job *job);
void		wait_for_job(t_core *shell, t_lst *jobs, t_job *job);
int8_t		mark_process_status
				(t_core *shell, t_lst *jobs, pid_t pid, int status);
void		mark_job_as_stopped(t_job *job, int8_t stopped);
int8_t		launch_blt(t_core *shell, t_process *process);
void		wait_for_process(t_core *shell, t_job *job, t_process *process);
void		update_status(t_core *shell);
t_job		*get_job(t_lst *jobs, char *str);
t_job		*get_job_by_id(t_lst *jobs, int id);
void		format_job_info(t_job *job);
int			update_jobs(t_lst *jobs);
void		attr_jobc_id(t_core *shell, t_job *job);
void		do_job_notification(t_core *shell, t_lst *job, int8_t free);
int			get_signal(int status);
int			cond(t_lst *process);
u_int8_t	are_jobs_done(t_core *shell, t_lst *jobs);
void		free_job(t_lst **job_list, t_lst *job);
void		rebuild_job_command(t_job *job);
char		*get_short_command(t_process *process);
void		split_job(t_core *shell, t_job *job);
char		*get_last_stop_status(t_job *job);

#endif
