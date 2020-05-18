/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 17:04:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*
**	LEXER_EXPANSION
*/

enum e_estate	find_expansion(const char *str);
char			*get_expansion(const char *string, enum e_estate state);
char			*exp_get_bracket(const char *string, size_t len);
char			*exp_get_dollar(const char *string, size_t len);
char			*exp_get_tilde(const char *string, size_t len);
char			*exp_get_tildep(const char *string, size_t len);
char			*exp_get_tildem(const char *string, size_t len);
size_t			get_index_expan(const char *str);

/*
**	EXPANSION_INHIBITEUR
*/
void			update_underscore_value
					(char *tmp, t_core *shell, t_process *process);
char			*inhibiteurs_expansion(char *data, t_core *shell, size_t flag);
char			*no_exp(const char *data, t_core *shell);
char			*exp_math(const char *data, t_core *shell);
char			*exp_tilde(const char *data, t_core *shell);
char			*exp_cmd_subs(const char *data, t_core *shell);
void			expansion(t_core *shell, t_process *process);
int8_t			add_assign_env(t_core *shell, const char *key, char *value);
void			add_assign_envp(const char *key, char *value, char ***envp);
char			**add_underscore_envp(char **envp, char *data);
u_int8_t		is_expansion(enum e_estate id);
t_expansion		*init_expansion_inhibiteurs(t_expansion *exp);
enum e_estate	skip_recur_quote(char *str, size_t *index, enum e_estate st);
enum e_estate	skip_quotes(char *str, t_expansion *exp);
u_int32_t		discard_backslash(const char *data, size_t *i, char **res);
u_int8_t		quotes_condition(char c, enum e_estate state);
t_expansion		*exp_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion		*word_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion		*start_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion		*quotes_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion		*discard_biteurs(char *dt, t_core *shell, t_expansion *exp);
void			expansion_tok(t_core *shell, t_process *process);
u_int8_t		check_tilde_path_exp(char *expandu, const char *str, size_t i);

/*
**	PARAM_EXPANSION
*/

char			*suffix_format(char *data, t_core *shell);
char			*prefix_format(char *data, t_core *shell);
char			*simple_format(char *str, t_core *shell);
char			*format_supplementaires(char *str, t_core *shell);
char			*questionmark_format(char **tablo, t_core *shell);
char			*length_format(char *str, t_core *shell);
char			*dash_format(char **tablo, t_core *shell);
char			*plus_format(char **tablo, t_core *shell);
char			*egal_format(char **tablo, t_core *shell);
char			*moar_format_plz(char *data, t_core *shell);
char			*get_brace_param(char *str, t_core *shell);
char			*exp_param(const char *data, t_core *shell);
char			*check_env_key(char *key, t_core *shell);
char			*one_moar_error(char **tablo, char *data, t_core *shell);
char			*error_brace_param(char *str, t_core *shell, char *tmp);
char			*check_env_key(char *key, t_core *shell);
u_int32_t		check_format_bracket(char c);
void			fill_thereste(char *str, char *tmp, int *index, int *i);
char			*tilde_param_exp(char *tablo, t_core *shell);
int				is_pos_vars(char c);
char			*pos_vars_format(char *str, t_core *shell);
#endif
