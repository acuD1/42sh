/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:29:49 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:54:57 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_start_analyze(t_anal analyze)
{
	analyze[A_START][P_NEWLINE] = separator_analyze;
	// analyze[A_START][P_ANDIF] = separator_analyze;
	// analyze[A_START][P_AND] = separator_analyze;
	// analyze[A_START][P_ORIF] = separator_analyze;
	// analyze[A_START][P_PIPE] = separator_analyze;
	// analyze[A_START][P_SEMICOLON] = separator_analyze;
	// analyze[A_START][P_DSEMI] = separator_analyze;

	analyze[A_START][P_DLESSDASH] = redirect_analyze;
	analyze[A_START][P_DLESS] = redirect_analyze;
	// analyze[A_START][P_DLESSDASH] = heredoc_analyze;
	// analyze[A_START][P_DLESS] = heredoc_analyze;
	analyze[A_START][P_LESSAND] = redirect_analyze;
	analyze[A_START][P_LESS] = redirect_analyze;
	analyze[A_START][P_DGREAT] = redirect_analyze;
	analyze[A_START][P_GREATAND] = redirect_analyze;
	analyze[A_START][P_GREAT] = redirect_analyze;
	analyze[A_START][P_IONUMBER] = ionbr_analyze;

	analyze[A_START][P_ASSIGN] = assign_analyze;

	analyze[A_START][P_ESCSEQ] = cmd_analyze;
	analyze[A_START][P_WORD] = cmd_analyze;
	analyze[A_START][P_QUOTE] = cmd_analyze;
	analyze[A_START][P_DBQUOTE] = cmd_analyze;
	analyze[A_START][P_BQUOTE] = cmd_analyze;
	analyze[A_START][P_DBPARENT] = cmd_analyze;
	analyze[A_START][P_PARENT] = cmd_analyze;
	analyze[A_START][P_BRACKET] = cmd_analyze;
	analyze[A_START][P_HOOK] = cmd_analyze;
	analyze[A_START][P_DOLLAR] = cmd_analyze;
	analyze[A_START][P_TILDE] = cmd_analyze;
	analyze[A_START][P_TILDEM] = cmd_analyze;
	analyze[A_START][P_TILDEP] = cmd_analyze;

	analyze[A_START][P_END] = end_analyze;
}

void		init_word_analyze(t_anal analyze)
{
	analyze[A_WORD][P_NEWLINE] = separator_analyze;
	analyze[A_WORD][P_ANDIF] = separator_analyze;
	analyze[A_WORD][P_AND] = separator_analyze;
	analyze[A_WORD][P_ORIF] = separator_analyze;
	analyze[A_WORD][P_PIPE] = separator_analyze;
	analyze[A_WORD][P_SEMICOLON] = separator_analyze;
	analyze[A_WORD][P_DSEMI] = separator_analyze;

	analyze[A_WORD][P_DLESSDASH] = redirect_analyze;
	analyze[A_WORD][P_DLESS] = redirect_analyze;
	// analyze[A_WORD][P_DLESSDASH] = heredoc_analyze;
	// analyze[A_WORD][P_DLESS] = heredoc_analyze;

	analyze[A_WORD][P_LESS] = redirect_analyze;
	analyze[A_WORD][P_DGREAT] = redirect_analyze;
	analyze[A_WORD][P_GREATAND] = redirect_analyze;
	analyze[A_WORD][P_LESSAND] = redirect_analyze;
	analyze[A_WORD][P_GREAT] = redirect_analyze;
	analyze[A_WORD][P_IONUMBER] = ionbr_analyze;
	
	analyze[A_WORD][P_ASSIGN] = assign_analyze;
	
	analyze[A_WORD][P_ESCSEQ] = cmd_analyze;
	analyze[A_WORD][P_WORD] = cmd_analyze;
	analyze[A_WORD][P_QUOTE] = cmd_analyze;
	analyze[A_WORD][P_DBQUOTE] = cmd_analyze;
	analyze[A_WORD][P_BQUOTE] = cmd_analyze;
	analyze[A_WORD][P_DBPARENT] = cmd_analyze;
	analyze[A_WORD][P_PARENT] = cmd_analyze;
	analyze[A_WORD][P_BRACKET] = cmd_analyze;
	analyze[A_WORD][P_HOOK] = cmd_analyze;
	analyze[A_WORD][P_DOLLAR] = cmd_analyze;
	analyze[A_WORD][P_TILDEM] = cmd_analyze;
	analyze[A_WORD][P_TILDEP] = cmd_analyze;
	analyze[A_WORD][P_TILDE] = cmd_analyze;

	analyze[A_WORD][P_END] = end_analyze;
}

static void	init_lereste(t_anal analyze)
{

	analyze[A_END][P_IONUMBER] = ionbr_analyze;
	analyze[A_END][P_ASSIGN] = assign_analyze;
	analyze[A_END][P_END] = end_analyze;
	analyze[A_SEPARATOR][P_IONUMBER] = ionbr_analyze;
	analyze[A_SEPARATOR][P_ASSIGN] = assign_analyze;

	analyze[A_END][P_LESSAND] = redirect_analyze;
}

static void	bzero_analyze(t_anal parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < NB_ANALYZER_STATE)
	{
		state = 0;
		while (state < NB_PARSER_STATE)
			parsing[index][state++] = error_analyze;
		++index;
	}
}

t_analyzer	*init_analyze(t_analyzer *analyzer, t_lst *lexer)
{
	if (!(analyzer = (t_analyzer*)malloc(sizeof(t_analyzer))))
		return (NULL);
	bzero_analyze(analyzer->analyze);
	init_process(&analyzer->process);
	init_redir(&analyzer->redir);
	init_job(&analyzer->job);
	init_assign(&analyzer->db);
	init_start_analyze(analyzer->analyze);
	init_ionumber_analyze(analyzer->analyze);
	init_assign_analyze(analyzer->analyze);
	init_word_analyze(analyzer->analyze);
	init_separator_analyze(analyzer->analyze);
	init_redirect_analyze(analyzer->analyze);
	init_end_analyze(analyzer->analyze);
	init_lereste(analyzer->analyze);
	analyzer->state = A_START;
	analyzer->lexer = lexer;
	analyzer->job_list = NULL;
	analyzer->redir_list = NULL;
	analyzer->process_list = NULL;
	return (analyzer);
}
