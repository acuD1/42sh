#include "sh42.h"

// void init_assign_analyze(t_anal analyze)
// {
// 	analyze[A_ASSIGN][P_NEWLINE] =
// 	analyze[A_ASSIGN][P_ANDIF] =
// 	analyze[A_ASSIGN][P_AND] =
// 	analyze[A_ASSIGN][P_ORIF] =
// 	analyze[A_ASSIGN][P_PIPE] =
// 	analyze[A_ASSIGN][P_DSEMI] =
// 	analyze[A_ASSIGN][P_SEMICOLON] =
// 	analyze[A_ASSIGN][P_DLESSDASH] =
// 	analyze[A_ASSIGN][P_DLESS] =
// 	analyze[A_ASSIGN][P_LESSGREAT] =
// 	analyze[A_ASSIGN][P_LESS] =
// 	analyze[A_ASSIGN][P_DGREAT] =
// 	analyze[A_ASSIGN][P_GREATAND] =
// 	analyze[A_ASSIGN][P_CLOBBER] =
// 	analyze[A_ASSIGN][P_GREAT] =
// 	analyze[A_ASSIGN][P_IONUMBER] =
// 	analyze[A_ASSIGN][P_ASSIGN] =
// 	analyze[A_ASSIGN][P_WORD] =
// 	analyze[A_ASSIGN][P_END] =
// }

void init_create_redir_analyze(t_anal analyze)
{
	analyze[A_CREATE_REDIR][P_NEWLINE] = error_analyze;
	analyze[A_CREATE_REDIR][P_ANDIF] = error_analyze;
	analyze[A_CREATE_REDIR][P_AND] = error_analyze;
	analyze[A_CREATE_REDIR][P_ORIF] = error_analyze;
	analyze[A_CREATE_REDIR][P_PIPE] = error_analyze;
	analyze[A_CREATE_REDIR][P_DSEMI] = error_analyze;
	analyze[A_CREATE_REDIR][P_SEMICOLON] =  error_analyze;
	analyze[A_CREATE_REDIR][P_DLESSDASH] = redir_analyze;
	analyze[A_CREATE_REDIR][P_DLESS] = redir_analyze;
	analyze[A_CREATE_REDIR][P_LESSGREAT] = redir_analyze;
	analyze[A_CREATE_REDIR][P_LESS] = redir_analyze;
	analyze[A_CREATE_REDIR][P_DGREAT] = redir_analyze;
	analyze[A_CREATE_REDIR][P_GREATAND] = redir_analyze;
	analyze[A_CREATE_REDIR][P_CLOBBER] = redir_analyze;
	analyze[A_CREATE_REDIR][P_GREAT] =	redir_analyze;
	analyze[A_CREATE_REDIR][P_IONUMBER] = error_analyze;
	analyze[A_CREATE_REDIR][P_ASSIGN] = assign_analyze;
	analyze[A_CREATE_REDIR][P_WORD] = cmd_analyze;
	analyze[A_CREATE_REDIR][P_END] = end_analyze;
}

void init_create_process_analyze(t_anal analyze)
{
	analyze[A_CREATE_PROCESS][P_NEWLINE] = process_analyze;
	analyze[A_CREATE_PROCESS][P_ANDIF] = error_analyze;
	analyze[A_CREATE_PROCESS][P_AND] = process_analyze;
	analyze[A_CREATE_PROCESS][P_ORIF] = error_analyze;
	analyze[A_CREATE_PROCESS][P_PIPE] = error_analyze;
	analyze[A_CREATE_PROCESS][P_DSEMI] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_SEMICOLON] =  process_analyze;
	analyze[A_CREATE_PROCESS][P_DLESSDASH] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_DLESS] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_LESSGREAT] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_LESS] = cmd_analyze;
	analyze[A_CREATE_PROCESS][P_DGREAT] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_GREATAND] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_CLOBBER] = redirect_analyze;
	analyze[A_CREATE_PROCESS][P_GREAT] =	redirect_analyze;
	analyze[A_CREATE_PROCESS][P_IONUMBER] = error_analyze;
	analyze[A_CREATE_PROCESS][P_ASSIGN] = error_analyze;
	analyze[A_CREATE_PROCESS][P_WORD] = cmd_analyze;
	analyze[A_CREATE_PROCESS][P_END] = end_analyze;
}

void init_create_job_analyze(t_anal analyze)
{
	analyze[A_CREATE_JOB][P_NEWLINE] = job_analyze;
	analyze[A_CREATE_JOB][P_ANDIF] = job_analyze;
	analyze[A_CREATE_JOB][P_AND] = process_analyze;
	analyze[A_CREATE_JOB][P_ORIF] = job_analyze;
	analyze[A_CREATE_JOB][P_PIPE] = redirect_analyze;
	analyze[A_CREATE_JOB][P_DSEMI] = redirect_analyze;
	analyze[A_CREATE_JOB][P_SEMICOLON] =  job_analyze;
	analyze[A_CREATE_JOB][P_DLESSDASH] = redirect_analyze;
	analyze[A_CREATE_JOB][P_DLESS] = redirect_analyze;
	analyze[A_CREATE_JOB][P_LESSGREAT] = redirect_analyze;
	analyze[A_CREATE_JOB][P_LESS] = cmd_analyze;
	analyze[A_CREATE_JOB][P_DGREAT] = redirect_analyze;
	analyze[A_CREATE_JOB][P_GREATAND] = redirect_analyze;
	analyze[A_CREATE_JOB][P_CLOBBER] = redirect_analyze;
	analyze[A_CREATE_JOB][P_GREAT] =	redirect_analyze;
	analyze[A_CREATE_JOB][P_IONUMBER] = error_analyze;
	analyze[A_CREATE_JOB][P_ASSIGN] = assign_analyze;
	analyze[A_CREATE_JOB][P_WORD] = cmd_analyze;
	analyze[A_CREATE_JOB][P_END] = end_analyze;
}

void init_ionumber_analyze(t_anal analyze)
{
	analyze[A_IONUMBER][P_NEWLINE] = end_analyze;
	analyze[A_IONUMBER][P_ANDIF] = redirect_analyze;
	analyze[A_IONUMBER][P_AND] = redirect_analyze;
	analyze[A_IONUMBER][P_ORIF] = redirect_analyze;
	analyze[A_IONUMBER][P_PIPE] = redirect_analyze;
	analyze[A_IONUMBER][P_DSEMI] = redirect_analyze;
	analyze[A_IONUMBER][P_SEMICOLON] =  end_analyze;
	analyze[A_IONUMBER][P_DLESSDASH] = redirect_analyze;
	analyze[A_IONUMBER][P_DLESS] = redirect_analyze;
	analyze[A_IONUMBER][P_LESSGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_LESS] = cmd_analyze;
	analyze[A_IONUMBER][P_DGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_GREATAND] = redirect_analyze;
	analyze[A_IONUMBER][P_CLOBBER] = redirect_analyze;
	analyze[A_IONUMBER][P_GREAT] =	redirect_analyze;
	analyze[A_IONUMBER][P_IONUMBER] = error_analyze;
	analyze[A_IONUMBER][P_ASSIGN] = assign_analyze;
	analyze[A_IONUMBER][P_WORD] = cmd_analyze;
	analyze[A_IONUMBER][P_END] = end_analyze;
	// analyze[A_IOFILE][P_WORD] = cmd_analyze;
}

void init_redirect_analyze(t_anal analyze)
{
	analyze[A_REDIRECT][P_NEWLINE] = end_analyze;
	analyze[A_REDIRECT][P_ANDIF] = error_analyze;
	analyze[A_REDIRECT][P_AND] = error_analyze;
	analyze[A_REDIRECT][P_ORIF] = error_analyze;
	analyze[A_REDIRECT][P_PIPE] = error_analyze;
	analyze[A_REDIRECT][P_DSEMI] = error_analyze;
	analyze[A_REDIRECT][P_SEMICOLON] =  end_analyze;
	analyze[A_REDIRECT][P_DLESSDASH] = error_analyze;
	analyze[A_REDIRECT][P_DLESS] = error_analyze;
	analyze[A_REDIRECT][P_LESSGREAT] = error_analyze;
	analyze[A_REDIRECT][P_LESS] = cmd_analyze;
	analyze[A_REDIRECT][P_DGREAT] = error_analyze;
	analyze[A_REDIRECT][P_GREATAND] = error_analyze;
	analyze[A_REDIRECT][P_CLOBBER] = error_analyze;
	analyze[A_REDIRECT][P_GREAT] =	error_analyze;
	analyze[A_REDIRECT][P_IONUMBER] = ionbr_analyze;
	analyze[A_REDIRECT][P_ASSIGN] = assign_analyze;
	analyze[A_REDIRECT][P_WORD] = cmd_analyze;
	analyze[A_REDIRECT][P_END] = end_analyze;
}

void init_end_analyze(t_anal analyze)
{
	analyze[A_END][P_NEWLINE] = end_analyze;
	analyze[A_END][P_ANDIF] = redirect_analyze;
	analyze[A_END][P_AND] = end_analyze;
	analyze[A_END][P_ORIF] = redirect_analyze;
	analyze[A_END][P_PIPE] = redirect_analyze;
	analyze[A_END][P_DSEMI] = separator_analyze;
	analyze[A_END][P_SEMICOLON] = end_analyze;
	analyze[A_END][P_DLESSDASH] = redirect_analyze;
	analyze[A_END][P_DLESS] = redirect_analyze;
	analyze[A_END][P_LESSGREAT] = redirect_analyze;
	analyze[A_END][P_LESS] = redirect_analyze;
	analyze[A_END][P_DGREAT] = redirect_analyze;
	analyze[A_END][P_GREATAND] = redirect_analyze;
	analyze[A_END][P_CLOBBER] = redirect_analyze;
	analyze[A_END][P_GREAT] = redirect_analyze;
	analyze[A_END][P_IONUMBER] = ionbr_analyze;
	analyze[A_END][P_ASSIGN] = assign_analyze;
	analyze[A_END][P_WORD] = cmd_analyze;
	analyze[A_END][P_END] = end_analyze;
}

void	init_separator_analyze(t_anal analyze)
{
	analyze[A_SEPARATOR][P_WORD] = cmd_analyze;
	analyze[A_SEPARATOR][P_GREAT] = end_analyze;
	analyze[A_SEPARATOR][P_GREATAND] = end_analyze;
	analyze[A_SEPARATOR][P_LESS] = end_analyze;
	analyze[A_SEPARATOR][P_LESSAND] = end_analyze;
	analyze[A_SEPARATOR][P_DGREAT] = end_analyze;
	analyze[A_SEPARATOR][P_DLESS] = end_analyze;
	analyze[A_SEPARATOR][P_DLESSDASH] = end_analyze;
	analyze[A_SEPARATOR][P_ANDDGREAT] = end_analyze;
	analyze[A_SEPARATOR][P_SEMICOLON] = end_analyze;
	analyze[A_SEPARATOR][P_NEWLINE] = end_analyze;
	analyze[A_SEPARATOR][P_END] = end_analyze;
}

void init_start_analyze(t_anal analyze)
{
	analyze[A_START][P_NEWLINE] = separator_analyze;
	analyze[A_START][P_ANDIF] = job_analyze;
	analyze[A_START][P_AND] = redirect_analyze;
	analyze[A_START][P_ORIF] = job_analyze;
	analyze[A_START][P_PIPE] = redirect_analyze;
	analyze[A_START][P_DSEMI] = separator_analyze;
	analyze[A_START][P_SEMICOLON] = separator_analyze;
	analyze[A_START][P_DLESSDASH] = redirect_analyze;
	analyze[A_START][P_DLESS] = redirect_analyze;
	analyze[A_START][P_LESSGREAT] = redirect_analyze;
	analyze[A_START][P_LESS] = redirect_analyze;
	analyze[A_START][P_DGREAT] = redirect_analyze;
	analyze[A_START][P_ANDDGREAT] = redirect_analyze;
	analyze[A_START][P_ANDGREAT] = redirect_analyze;
	analyze[A_START][P_GREATAND] = redirect_analyze;
	analyze[A_START][P_CLOBBER] = redirect_analyze;
	analyze[A_START][P_GREAT] = redirect_analyze;
	analyze[A_START][P_IONUMBER] = ionbr_analyze;
	analyze[A_START][P_ASSIGN] = assign_analyze;
	analyze[A_START][P_WORD] = cmd_analyze;
	analyze[A_START][P_END] = end_analyze;
}

void init_word_analyze(t_anal analyze)
{
	analyze[A_WORD][P_NEWLINE] = job_analyze;
	analyze[A_WORD][P_ANDIF] = job_analyze;
	analyze[A_WORD][P_AND] = process_analyze;
	analyze[A_WORD][P_ORIF] = job_analyze;
	analyze[A_WORD][P_PIPE] = redirect_analyze;
	analyze[A_WORD][P_DSEMI] = error_analyze;
	analyze[A_WORD][P_SEMICOLON] = process_analyze;
	analyze[A_WORD][P_DLESSDASH] = redirect_analyze;
	analyze[A_WORD][P_DLESS] = redirect_analyze;
	analyze[A_WORD][P_LESSGREAT] = redirect_analyze;
	analyze[A_WORD][P_LESS] = redirect_analyze;
	analyze[A_WORD][P_DGREAT] = redirect_analyze;
	analyze[A_WORD][P_GREATAND] = redirect_analyze;
	analyze[A_WORD][P_ANDDGREAT] = redirect_analyze;
	analyze[A_WORD][P_ANDGREAT] = redirect_analyze;
	analyze[A_WORD][P_CLOBBER] = redirect_analyze;
	analyze[A_WORD][P_GREAT] = redirect_analyze;
	analyze[A_WORD][P_IONUMBER] = ionbr_analyze;
	analyze[A_WORD][P_ASSIGN] = assign_analyze;
	analyze[A_WORD][P_WORD] = cmd_analyze;
	analyze[A_WORD][P_END] = end_analyze;
}

// void init_cmd_analyze(t_anal analyze)
// {
// 	analyze[A_CMD][P_NEWLINE] = separator_analyze;
// 	analyze[A_CMD][P_ANDIF] = redirect_analyze;
// 	analyze[A_CMD][P_AND] = redirect_analyze;
// 	analyze[A_CMD][P_ORIF] = redirect_analyze;
// 	analyze[A_CMD][P_PIPE] = redirect_analyze;
// 	analyze[A_CMD][P_DSEMI] = separator_analyze;
// 	analyze[A_CMD][P_SEMICOLON] = separator_analyze;
// 	analyze[A_CMD][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CMD][P_DLESS] = redirect_analyze;
// 	analyze[A_CMD][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CMD][P_LESS] = redirect_analyze;
// 	analyze[A_CMD][P_DGREAT] = redirect_analyze;
// 	analyze[A_CMD][P_GREATAND] = redirect_analyze;
// 	analyze[A_CMD][P_CLOBBER] = redirect_analyze;
// 	analyze[A_CMD][P_GREAT] = redirect_analyze;
// 	analyze[A_CMD][P_IONUMBER] = ionbr_analyze;
// 	analyze[A_CMD][P_ASSIGN] = assign_analyze;
// 	analyze[A_CMD][P_WORD] = cmd_analyze;
// 	analyze[A_CMD][P_END] = end_analyze;
// }

// void init_cmd_arg_analyze(t_anal analyze)
// {
// 	analyze[A_CMD_ARG][P_NEWLINE] = separator_analyze;
// 	analyze[A_CMD_ARG][P_ANDIF] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_AND] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_ORIF] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_PIPE] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DSEMI] = separator_analyze;
// 	analyze[A_CMD_ARG][P_SEMICOLON] = separator_analyze;
// 	analyze[A_CMD_ARG][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DLESS] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_LESS] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DGREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_GREATAND] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_CLOBBER] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_GREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_IONUMBER] = ionbr_analyze;
// 	analyze[A_CMD_ARG][P_ASSIGN] = assign_analyze;
// 	analyze[A_CMD_ARG][P_WORD] = cmd_analyze;
// 	analyze[A_CMD_ARG][P_END] = end_analyze;
// }

static void	bzero_analyze(t_anal parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < NB_ANALYZER_STATE)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parsing[index][state++] = error_analyze;
		++index;
	}
}

t_analyzer *init_analyze(t_analyzer *analyzer, t_core *shell)
{
	if (!(analyzer = (t_analyzer*)malloc(sizeof(t_analyzer))))
		return (NULL);
	bzero_analyze(analyzer->analyze);
	init_start_analyze(analyzer->analyze);
	// init_create_job_analyze(analyzer->analyze);
	// init_create_job_analyze(analyzer->analyze);
	// init_create_job_analyze(analyzer->analyze)
	init_ionumber_analyze(analyzer->analyze);
	// init_assign_analyze(analyzer->analyze);
	init_word_analyze(analyzer->analyze);
	// init_cmd_analyze(analyzer->analyze);
	// init_cmd_arg_analyze(analyzer->analyze);
	init_separator_analyze(analyzer->analyze);
	init_redirect_analyze(analyzer->analyze);
	init_end_analyze(analyzer->analyze);
	analyzer->state = A_START;
	analyzer->lexer = shell->lexer;
	init_process(&analyzer->process);
	analyzer->job_list = NULL;
	init_job(&analyzer->job);
	init_redir(&analyzer->redir);
	return (analyzer);
}