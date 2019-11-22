#include "sh42.h"

void init_expansion_analyze(t_anal analyze)
{
	analyze[A_START][P_START] = separator_analyze;
	analyze[A_EXPANSION][P_NEWLINE] = separator_analyze;
	analyze[A_EXPANSION][P_ANDIF] = separator_analyze;
	analyze[A_EXPANSION][P_AND] = separator_analyze;
	analyze[A_EXPANSION][P_ORIF] = separator_analyze;
	analyze[A_EXPANSION][P_PIPE] = separator_analyze;
	analyze[A_EXPANSION][P_DSEMI] = error_analyze;
	analyze[A_EXPANSION][P_SEMICOLON] = separator_analyze;
	analyze[A_EXPANSION][P_DLESSDASH] = redirect_analyze;
	analyze[A_EXPANSION][P_DLESS] = redirect_analyze;
	analyze[A_EXPANSION][P_LESS] = redirect_analyze;
	analyze[A_EXPANSION][P_DGREAT] = redirect_analyze;
	analyze[A_EXPANSION][P_GREATAND] = redirect_analyze;
	analyze[A_EXPANSION][P_GREAT] = redirect_analyze;
	analyze[A_EXPANSION][P_IONUMBER] = ionbr_analyze;
	analyze[A_EXPANSION][P_ASSIGN] = assign_analyze;
	analyze[A_EXPANSION][P_WORD] = cmd_analyze;
	analyze[A_EXPANSION][P_ESCSEQ] = cmd_analyze;
	analyze[A_EXPANSION][P_DBPARENT] = cmd_analyze;
	analyze[A_EXPANSION][P_PARENT] = cmd_analyze;
	analyze[A_EXPANSION][P_BRACKET] = cmd_analyze;
	analyze[A_EXPANSION][P_HOOK] = cmd_analyze;
	analyze[A_EXPANSION][P_DOLLAR] = cmd_analyze;
	analyze[A_EXPANSION][P_TILDE] = cmd_analyze;
	analyze[A_EXPANSION][P_END] = end_analyze;
}

void init_start_analyze(t_anal analyze)
{
	analyze[A_START][P_START] = separator_analyze;
	analyze[A_START][P_NEWLINE] = separator_analyze;
	analyze[A_START][P_ANDIF] = separator_analyze;
	analyze[A_START][P_AND] = separator_analyze;
	analyze[A_START][P_ORIF] = separator_analyze;
	analyze[A_START][P_PIPE] = separator_analyze;
	analyze[A_START][P_DSEMI] = error_analyze;
	analyze[A_START][P_SEMICOLON] = separator_analyze;
	analyze[A_START][P_DLESSDASH] = redirect_analyze;
	analyze[A_START][P_DLESS] = redirect_analyze;
	analyze[A_START][P_LESS] = redirect_analyze;
	analyze[A_START][P_DGREAT] = redirect_analyze;
	analyze[A_START][P_GREATAND] = redirect_analyze;
	analyze[A_START][P_GREAT] = redirect_analyze;
	analyze[A_START][P_IONUMBER] = ionbr_analyze;
	analyze[A_START][P_ESCSEQ] = cmd_analyze;
	analyze[A_START][P_ASSIGN] = assign_analyze;
	analyze[A_START][P_WORD] = cmd_analyze;
	analyze[A_START][P_DBPARENT] = cmd_analyze;
	analyze[A_START][P_PARENT] = cmd_analyze;
	analyze[A_START][P_BRACKET] = cmd_analyze;
	analyze[A_START][P_HOOK] = cmd_analyze;
	analyze[A_START][P_DOLLAR] = cmd_analyze;
	analyze[A_START][P_TILDE] = cmd_analyze;
	analyze[A_START][P_END] = end_analyze;
}

void init_word_analyze(t_anal analyze)
{
	analyze[A_WORD][P_NEWLINE] = separator_analyze;
	analyze[A_WORD][P_ANDIF] = separator_analyze;
	analyze[A_WORD][P_AND] = separator_analyze;
	analyze[A_WORD][P_ORIF] = separator_analyze;
	analyze[A_WORD][P_PIPE] = separator_analyze;
	analyze[A_WORD][P_DSEMI] = error_analyze;
	analyze[A_WORD][P_SEMICOLON] = separator_analyze;
	analyze[A_WORD][P_DLESSDASH] = redirect_analyze;
	analyze[A_WORD][P_DLESS] = redirect_analyze;
	analyze[A_WORD][P_LESS] = redirect_analyze;
	analyze[A_WORD][P_DGREAT] = redirect_analyze;
	analyze[A_WORD][P_GREATAND] = redirect_analyze;
	analyze[A_WORD][P_GREAT] = redirect_analyze;
	analyze[A_WORD][P_IONUMBER] = ionbr_analyze;
	analyze[A_WORD][P_ASSIGN] = assign_analyze;
	analyze[A_WORD][P_WORD] = cmd_analyze;
	analyze[A_WORD][P_ESCSEQ] = cmd_analyze;
	analyze[A_WORD][P_DBPARENT] = cmd_analyze;
	analyze[A_WORD][P_PARENT] = cmd_analyze;
	analyze[A_WORD][P_BRACKET] = cmd_analyze;
	analyze[A_WORD][P_HOOK] = cmd_analyze;
	analyze[A_WORD][P_DOLLAR] = cmd_analyze;
	analyze[A_WORD][P_TILDE] = cmd_analyze;
	analyze[A_WORD][P_END] = end_analyze;
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

t_analyzer *init_analyze(t_analyzer *analyzer, t_core *shell)
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
	init_expansion_analyze(analyzer->analyze);
	analyzer->state = A_START;
	analyzer->lexer = shell->lexer;
	analyzer->job_list = NULL;
	analyzer->assign_list = NULL;
	analyzer->redir_list = NULL;
	analyzer->process_list = NULL;
	analyzer->tmp_list = NULL;
	return (analyzer);
}
