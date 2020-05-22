/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:53:44 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 20:59:34 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_ANALYZER_H
# define LEXER_PARSER_ANALYZER_H

void		lexer_parser_analyzer(t_core *shell);

/*
**	ANALYZER
*/

t_analyzer	*load_heredoc_fromline(t_analyzer *anal, t_core *shell);
t_analyzer	*heredoc_analyzer(t_analyzer *anal, t_core *shell);
t_analyzer	*exit_lpa(t_analyzer *anal, t_core *shell);
t_analyzer	*init_analyze(t_analyzer *analyzer, t_lst *lexer);
void		init_redir(t_redir *new);
void		init_process(t_process *new);
void		init_job(t_job *new);
void		init_assign(t_db *db);
void		init_assign_analyze(t_anal analyze);
void		init_ionumber_analyze(t_anal analyze);
void		init_redirect_analyze(t_anal analyze);
void		init_end_analyze(t_anal analyze);
void		init_separator_analyze(t_anal analyze);
void		analyzer(t_core *shell, t_lst *lexer);
t_analyzer	*cmd_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*end_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*separator_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*redirect_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*error_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*ionbr_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*assign_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*redir_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*redir_wanalyze(t_analyzer *anal, t_core *shell);
t_analyzer	*process_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*job_analyze(t_analyzer *analyzer, t_core *shell);
t_analyzer	*process_word_analyze(t_analyzer *anal);
void		free_process_list(t_lst **head);
void		ft_free_redirlist(t_lst **head);
char		*fill_cmd_job(t_lst *tok_lst, char *cmd);
char		**ft_add_arg_cmd_process(char **tablo, const char *str);
char		*join_one_char(char *dst, char *str, size_t index);
t_analyzer	*add_process(t_analyzer *anal, t_core *shell);
/*
**	PARSER
*/

u_int8_t	parser(t_lst *lexer);
u_int8_t	graph(enum e_pstate *c, enum e_pstate n, enum e_pstate ps[]);
void		init_start_graph(t_graph *graph);
void		init_word_graph(t_graph *graph);
void		init_redirect_graph(t_graph *graph);
void		init_process_graph(t_graph *graph);
void		init_ionumber_graph(t_graph *graph);

/*
**	LEXER
*/

size_t		get_word_size_ntype(size_t i, char *str);
size_t		loop_till_next_subprompt(const char *str, size_t i);
t_lst		*lexer(char *line);
t_lst		*start_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*end_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*name_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*newline_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*discard_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*number_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*assignement_word_lexer(t_lexer *lexer, t_lst *lexer_token);
t_lst		*operator_lexer(t_lexer *lexer, t_lst *lexer_token);
void		init_lexer(char *line, t_lexer *new);
t_token		*fetch_token(t_token *token, enum e_pstate type, const char *data);
void		ft_freejoblist(t_lst **lst);
void		ft_freetokenlist(t_lst **lst);

#endif
