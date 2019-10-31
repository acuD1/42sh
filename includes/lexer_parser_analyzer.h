/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:07:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/10/02 18:07:21 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_AST_H
# define LEXER_PARSER_AST_H

# include "sh42.h"

void lexer_parser_analyzer(t_core *shell, char *line);

/*
**  ANALYZER
*/

t_analyzer  *init_analyze(t_analyzer *analyzer, t_core *shell);
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

void        analyzer(t_core *shell);
void        cmd_analyze(t_analyzer *analyzer);
void        end_analyze(t_analyzer *analyzer);
void        separator_analyze(t_analyzer *analyzer);
void        redirect_analyze(t_analyzer *analyzer);
void        error_analyze(t_analyzer *analyzer);
void        ionbr_analyze(t_analyzer *analyzer);
void        assign_analyze(t_analyzer *analyzer);
void        redir_analyze(t_analyzer *analyzer);
void        process_analyze(t_analyzer *analyzer);
void        job_analyze(t_analyzer *analyzer);
void 		ass_analyze(t_analyzer *analyzer);


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

t_lst           *ft_lstadd(t_lst **curr, t_lst *new);
t_lst 			*lexer(char *line);
int				ft_isdigit(int c);
int 			ft_isalpha(int c);
void			start_lexer(t_lexer *lexer);
void			end_lexer(t_lexer *lexer);
void			name_lexer(t_lexer *lexer);
void			newline_lexer(t_lexer *lexer);
void			number_lexer(t_lexer *lexer);
void			assignement_word_lexer(t_lexer *lexer);
void			operator_lexer(t_lexer *lexer);
void			ft_printtoklist(t_lexer *lexer);
t_lst			*ft_add_token(t_lst **curr, e_parser_state opeid, char *data);
t_lexer			*init_lexer(char *line);
t_token 		*lexer_token_set(t_token *token, e_parser_state opeid, char *data);
t_lst			*ft_create_token(char *data, e_parser_state opeid);

#endif
