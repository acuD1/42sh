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

u_int8_t		is_expansion(enum e_estate id);
char			*do_expansion(t_core *shell, const char *data);
void			init_expansionat(t_expansion *exp);
void			expansion_assign(t_core *shell, t_process *process);
void			expansion_redir(t_core *shell, t_process *process);
void			expansion_tok(t_core *shell, t_process *process);
char			*exp_cmd_subs(const char *data, t_core *shell);
char			*no_exp(const char *data, t_core *shell);
char			*exp_math(const char *data, t_core *shell);
char			*exp_param(const char *data, t_core *shell);
char			*exp_tilde(const char *data, t_core *shell);
void			expansion(t_core *shell, t_process *process);
int				get_exp(const char *src, int *index, char **dst, t_core *shell);
char			*exp_get_tilde(const char *string, int len);
char			*exp_get_tildep(const char *string, int len);
char			*exp_get_tildem(const char *string, int len);
char			*exp_get_paren(const char *string, int len);
char			*exp_get_bracket(const char *string, int len);
char			*exp_get_dollar(const char *string, int len);
char			*exp_get_dbparen(const char *string, int len);
char			*exp_get_bquote(const char *string, int len);
char			*exp_get_hook(const char *string, int len);
enum e_estate	find_expansion(const char *str);
char			*get_expansion(const char *string, enum e_estate state);
char			*infinite_expansion(const char *data, t_core *shell);
char			*moar_format_plz(char *data, t_core *shell);
char			*suffix_format(char *data, t_core *shell);
char			*prefix_format(char *data, t_core *shell);
int8_t			add_assign_env(t_core *shell, const char *key, char *value);
char			*length_format(char *str, t_core *shell);
char			*check_env_key(char *key, t_core *shell);
char			*questionmark_format(char **tablo, t_core *shell);
char			*error_moar_format_third(char **tablo, char *data);
char			*check_env_key(char *key, t_core *shell);
char			*double_two_point_param(char **tablo, t_core *shell);
char			*error_moar_format_bis(char *data);
char			*error_moar_format_param(char **tablo, char *data);
char			*get_two_point_param_exp(char **tablo, t_core *shell);
enum e_estate	skip_quotes(const char *str, int *j, enum e_estate st);
char			*quote_backslash_discarder(const char *data);
#endif
