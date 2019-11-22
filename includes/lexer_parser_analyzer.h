/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:07:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/18 15:29:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_AST_H
# define LEXER_PARSER_AST_H

# include "sh42.h"

int8_t debug_ailleurs(const char *path, const char *str);
int getlefdpour_debug_ailleurs(const char *path);

void 	lexer_parser_analyzer(t_core *shell, char *line);


t_analyzer 	*expansion_analyze(t_analyzer *analyzer, t_core *shell);
uint8_t		expansion(t_core *shell, t_process *process);
char 		*exp_dbparen(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_hook(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_paren(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_bracket(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_dollar(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_tilde(char *expansion, t_core *shell, e_parser_state id);
char 		*exp_error(char *expansion, t_core *shell, e_parser_state id);
char 		*cmd_substitution_expansion(t_token *token, t_core *shell);

uint8_t is_expansion(enum parser_state id);

/*
**  ANALYZER
*/

t_analyzer	*init_analyze(t_analyzer *analyzer, t_core *shell);
void        init_redir(t_redir *new);
void        init_process(t_process *new);
void        init_job(t_job *new);
void 		init_assign(t_db *db);
void        init_start_analyze(t_anal analyze);
void        init_word_analyze(t_anal analyze);
void        init_assign_analyze(t_anal analyze);
void        init_ionumber_analyze(t_anal analyze);
void        init_redirect_analyze(t_anal analyze);
void        init_end_analyze(t_anal analyze);
void        init_separator_analyze(t_anal analyze);

void 		analyzer(t_core *shell);
t_analyzer  *cmd_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *end_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *separator_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *redirect_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *error_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *ionbr_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *assign_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer 	*redir_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *process_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer  *job_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer 	*ass_analyze(t_analyzer *analyzer, t_core *shell);


t_db 		*fetch_assign(t_db *assign);
t_job       *fetch_job(t_job *job);
t_redir     *fetch_redir(t_redir *redir);
t_process   *fetch_process(t_process *process);
void        get_token(t_analyzer *analyzer);
void        ft_free_processlist(t_lst **head);
void        ft_free_redirlist(t_lst **head);
void        ft_free_redir(t_redir *redir);

char        *fill_cmd_job(t_analyzer *analyzer, int flag);
char 		**fill_cmd_process(char *str);
char 		**ft_add_arg_cmd_process(char **tablo, char *str);

void        ft_printtab(char **cmd);
void        ft_printredir(t_redir *redir);
void        ft_printprocess(t_process *process);
void        ft_printjob(t_job *job);
void        ft_printjoblst(t_lst *list);
void 		ft_printassignlist(t_lst *lst);

/*
**  PARSER
*/

uint8_t     parser(t_lst *lexer);
void        init_word_graph(t_graph *graph);
void        init_redirect_graph(t_graph *graph);
void        init_process_graph(t_graph *graph);
void        init_assign_graph(t_graph *graph);
void        init_ionumber_graph(t_graph *graph);
void        init_start_graph(t_graph *graph);
t_parser    *ft_init_graph(t_parser *parser);

/*
**  LEXER
*/

t_lst	 		*lexer(char *line);

int				ft_isdigit(int c);
int 			ft_isalpha(int c);


t_lst			*expansion_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst 			*exp_dbparen_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token);
t_lst 			*exp_paren_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token);
t_lst 			*exp_bracket_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token);
t_lst 			*exp_dollar_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token);
t_lst 			*exp_tilde_lexer(t_lexer *lexer, e_parser_state id, int len, t_lst *lexer_token);

t_lst			*start_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*end_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*name_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*newline_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*backslash_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*number_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*assignement_word_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst			*operator_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst 			*word_lexer(t_lexer *lexer, t_lst *lexer_token);

void 			init_lexer(char *line ,t_lexer *new);
void 			init_token(t_token *token);
t_token			*fetch_lexer_token(t_token *token, e_parser_state type, char *data);

void			ft_printtoklist(t_lst *lexer);

void ft_freejoblist(t_lst **lst);
void ft_freetokenlist(t_lst **lst);
void ft_freedblist(t_lst **lst);

#endif
