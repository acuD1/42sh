/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 18:43:17 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh42.h"

/*
**  QUOTE
*/

char *quote_removing(char *str);
char *quote_mechanisms(char *str);
// char *quote_removing(char *data, e_pstate id);
char *point_de_cote(char *src, char quote);



/*
**  EXPANSION
*/

char 	*do_expansion(t_core *shell, char *data);
void 	init_expansionat(t_expansion 	*exp);
uint8_t is_expansion(e_estate id);

int8_t		add_assign_env(t_lst *lst, t_core *shell);
void		expansion_assign(t_core *shell, t_process *process);

void		expansion_redir(t_core *shell, t_process *process);
void		expansion_tok(t_core *shell, t_process *process);

char *exp_cmd_subs(char *data, t_core *shell);
char *no_exp(char *data, t_core *shell);
char *exp_dbquote(char *data, t_core *shell);
char *exp_math(char *data, t_core *shell);
char *exp_param(char *data, t_core *shell);
char *exp_tilde(char *data, t_core *shell);

void	expansion(t_core *shell, t_process *process);
int		expelliarmus(char *src, int *index, char **dst, t_core *shell);

char		*exp_get_tilde(char *string, int len);
char		*exp_get_tildep(char *string, int len);
char		*exp_get_tildem(char *string, int len);
char		*exp_get_paren(char *string, int len);
char		*exp_get_bracket(char *string, int len);
char		*exp_get_dollar(char *string, int len);
char		*exp_get_dbparen(char *string, int len);
char		*exp_get_hook(char *string, int len);
char		*new_exp(char *string, e_estate id);
e_estate 	find_expansion(char *str);
char		*get_expansion(char *string, e_estate state);

char *do_exp_et_quote(t_core *shell, char *data);


int 	get_word_size_ntype(int i, char *str);


t_lst			*expansion_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst 			*exp_dbparen(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst 			*exp_paren_lexer(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst 			*exp_bracket_lexer(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst 			*exp_dollar_lexer(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst 			*exp_tilde_lexer(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst 			*exp_hook(t_lexer *lexer, e_estate id, int len, t_lst *lexer_token);
t_lst			*quote_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst 			*dbquote_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst 			*bquote_lexer(t_lexer *lexer, t_lst *lexer_token);



#endif


