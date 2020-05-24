/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/24 16:57:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

/*
**		CONFIGURATION
*/

int8_t		init_termcaps(t_read *term);
void		init_cmd_line(t_core *shell, t_read *term);
int8_t		init_config(t_core *shell);
int8_t		reset_config(t_core *shell);
int8_t		get_size(t_read *term);

/*
**		PROMPT
*/

int8_t		init_prompt(t_core *shell);
void		display_prompt(t_read *term);
void		goto_prompt(t_read *term);
void		get_prompt_value(t_core *shell, const char *key);

/*
**		CHECK CAPS AND INTERPRET
*/

u_int8_t	check_caps(const char *buff, t_core *shell);
void		check_keys_comb(t_read *term, u_int64_t value);
void		insert_in_buffer(const char *buf, t_read *term);
void		insert_char_in_buffer
				(const char buf, t_read *term, ssize_t buf_index);
void		insert_str_in_buffer(const char *d_name, t_read *term);

/*
**		ACTION KEYS
*/

void		move_right(t_read *term);
void		move_left(t_read *term);
void		move_key_up(t_read *term);
void		move_key_down(t_read *term);
void		move_in_column(u_int64_t value, t_read *term);
void		del_key(t_read *term);
void		bs_key(t_read *term);
void		clr_screen(t_read *term);
int8_t		tab_key(t_core *shell);

/*
**		HISTORY
*/

int8_t		init_history(t_core *shell);
int8_t		write_history(t_core *shell);
void		save_history(t_read *term);
void		research_mode(t_read *term);
int8_t		check_expansions(t_read *term);
void		insert_content(ssize_t j, ssize_t i, t_read *term, char *content);
int64_t		call_number(t_read *term, ssize_t i);
int64_t		callback_number(t_read *term, ssize_t i);
int64_t		call_word(t_read *term, ssize_t i);
int64_t		last_cmd_back(t_read *term, ssize_t i);
char		*get_home_value(t_core *shell);
void		goto_reverse(t_read *term, const char *buff_tmp);
void		walking_history(const char *buff, t_read *term, t_lst **history);
ssize_t		get_history_value(char *var);
ssize_t		check_exp_error(t_lst *w, ssize_t n);

/*
**		SUBPROMPT/MULTILINE
*/

void		display_subprompt(t_read *term);
ssize_t		check_subprompt(t_core *shell);
u_int8_t	check_backslash(t_read *term, char *quote);
u_int8_t	check_backslash_nbr(char *str, ssize_t *index);
u_int8_t	charset_count(t_read *term, char charset, size_t i);
u_int8_t	quotes_is_matching(t_read *term, char *quote);
void		load_subprompt(char quote, t_read *term);
u_int8_t	read_multiline(t_core *shell);
char		*add_keys_subprompt(char c, char *str);
char		*del_keys_subprompt(char c, char *str);
ssize_t		check_quote_priority(char *str, t_subprompt *sub);
enum e_subp	quote_subprompt(t_core *shell, t_subprompt *sub);
ssize_t		check_dbquote_priority(t_core *shell, t_subprompt *sub);
enum e_subp	dbquote_subprompt(t_core *shell, t_subprompt *sub);
ssize_t		open_machine_subprompt(t_core *shell, t_subprompt *sub);
enum e_subp	backslash_subprompt(t_core *shell, t_subprompt *sub);
void		reboot_or_end_machine(t_core *shell, t_subprompt *sub);
enum e_subp	braceparam_subprompt(t_core *shell, t_subprompt *sub);
void		del_keys_subprompt_and_move(t_subprompt *sub, char quote);
enum e_subp	start_subprompt(t_core *shell, t_subprompt *sub);
char		*load_heredoc(t_core *shell, const char *key);
u_int8_t	sub_prompt_error(t_read *term, char sb);
void		subprompt_loader(t_core *shell);

/*
**		AUTO COMPLETION
*/

size_t		get_max_len(size_t len, size_t new_len);
int8_t		auto_complete_mode(char *input, t_core *shell, char **completion);
u_int8_t	is_exec(char *path);
u_int8_t	last_is_slash(char *str);
void		display_ac_lst(t_auto_comp *ac);
char		**split_path(t_core *shell, const char *str);
char		*ac_parse_input(char *input, enum e_ac_type type);
char		*ac_tilde(char *input, t_core *shell);
void		ac_file(char *input, t_auto_comp *ac, t_core *shell);
void		ac_binary(char *input, t_auto_comp *ac, t_core *shell);
void		ac_variable(char *input, t_auto_comp *ac, t_core *shell);
void		ac_add_content(t_auto_comp *ac, char *path, char *d_name);
char		*ac_parse_input(char *input, enum e_ac_type type);
char		*get_dir_path(t_auto_comp *ac, char *input, char **path);

/*
**		TOOLS
*/

int			my_outc(int c);
ssize_t		get_width_last_line(t_read *term);
ssize_t		get_width_current_line(t_read *term);
u_int64_t	get_mask(const char *buff);
u_int8_t	is_dot(const char *d_name);
u_int8_t	is_dir(const char *dir);
void		free_lst(t_lst *lst);
void		xtputs(char *str, int i, int (*f)(int));

/*
**		CLIPBOARD
*/

void		ak_clipboard(t_read *term, const char *buff, u_int64_t *value);
void		load_selection(t_read *term, const char *buff, u_int64_t value);
void		copy_text(t_read *term, t_cmd copy);
void		paste_text(t_read *term);
void		cut_text(t_read *term, t_cmd copy);

#endif
