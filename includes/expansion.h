/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/13 18:14:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H


/*
**	LEXER_EXPANSION
*/

int				check_brackets_inbracket(int *count, char c);
enum e_estate	find_expansion(const char *str);
char			*get_expansion(const char *string, enum e_estate state);
char			*exp_get_bquote(const char *string, int len);
char			*exp_get_paren(const char *string, int len);
char			*exp_get_bracket(const char *string, int len);
char			*exp_get_dollar(const char *string, int len);
char			*exp_get_tilde(const char *string, int len);
char			*exp_get_tildep(const char *string, int len);
char			*exp_get_tildem(const char *string, int len);
char			*exp_get_hook(const char *string, int len);
char			*exp_get_dbparen(const char *string, int len);

/*
**	EXPANSION_INHIBITEUR
*/

char			*inhibiteurs_expansion(char *data, t_core *shell);
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

enum e_estate	skip_recur_quote(char *str, int *index, enum e_estate st);
enum e_estate	skip_quotes(char *str, t_expansion *exp);
int				discard_backslash(const char *data, int *i, char **res);
int 			quotes_condition(char c, enum e_estate state);


t_expansion 	*exp_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion 	*word_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion 	*start_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion 	*quotes_biteurs(char *data, t_core *shell, t_expansion *exp);
t_expansion 	*discard_biteurs(char *dt, t_core *shell, t_expansion *exp);

/*
**	PARAM_EXPANSION
*/


char			*suffix_format(char *data, t_core *shell);
char			*prefix_format(char *data, t_core *shell);
char			*simple_format(char *str, t_core *shell); //esh
char			*format_supplementaires(char *str, t_core *shell);
char			*questionmark_format(char **tablo, t_core *shell);
char			*length_format(char *str, t_core *shell);
char			*double_two_point_param(char **tablo, t_core *shell);
char			*dash_format(char **tablo, t_core *shell);
char			*plus_format(char **tablo, t_core *shell);
char			*egal_format(char **tablo, t_core *shell);
char			*underniercaspourlaroute(char **tablo, t_core *shell);
char			*moar_format_plz(char *data, t_core *shell);

char			*get_two_point_param_exp(char **tablo, t_core *shell);
char			*get_brace_param(char *str, t_core *shell);

char			*exp_param(const char *data, t_core *shell);
char			*check_env_key(char *key, t_core *shell);

char			*error_moar_format_third(char **tablo, char *data, t_core *shell);
char			*error_moar_format_bis(char *data, t_core *shell);
char			*error_moar_format_param(char **tablo, char *data, t_core *shell);
char			*one_moar_error(char **tablo, char *data, t_core *shell);
#endif
