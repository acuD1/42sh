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
// 	analyze[A_ASSIGN][P_GREAT] =
// 	analyze[A_ASSIGN][P_IONUMBER] =
// 	analyze[A_ASSIGN][P_ASSIGN] =
// 	analyze[A_ASSIGN][P_WORD] =
// 	analyze[A_ASSIGN][P_END] =
// }

// void init_create_redir_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_REDIR][P_NEWLINE] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_ANDIF] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_AND] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_ORIF] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_PIPE] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_DSEMI] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_SEMICOLON] =  error_analyze;
// 	analyze[A_CREATE_REDIR][P_DLESSDASH] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_DLESS] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_LESSGREAT] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_LESS] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_DGREAT] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_GREATAND] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_GREAT] =	redir_analyze;
// 	analyze[A_CREATE_REDIR][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_REDIR][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_REDIR][P_END] = separator_analyze;
// }

// void init_create_separator_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_PROCESS][P_NEWLINE] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_ANDIF] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_AND] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_ORIF] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_PIPE] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_DSEMI] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_SEMICOLON] =  separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_DLESS] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_LESS] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_DGREAT] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_GREATAND] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_GREAT] =	redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_PROCESS][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_PROCESS][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_PROCESS][P_END] = separator_analyze;
// }

// void init_create_job_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_JOB][P_NEWLINE] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_ANDIF] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_AND] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_ORIF] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_PIPE] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_DSEMI] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_SEMICOLON] =  separator_analyze;
// 	analyze[A_CREATE_JOB][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_DLESS] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_LESS] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_DGREAT] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_GREATAND] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_GREAT] =	redirect_analyze;
// 	analyze[A_CREATE_JOB][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_JOB][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_JOB][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_JOB][P_END] = end_analyze;
// }

void init_ionumber_analyze(t_anal analyze)
{
	analyze[A_IONUMBER][P_NEWLINE] = error_analyze;
	analyze[A_IONUMBER][P_ANDIF] = error_analyze;
	analyze[A_IONUMBER][P_AND] = error_analyze;
	analyze[A_IONUMBER][P_ORIF] = error_analyze;
	analyze[A_IONUMBER][P_PIPE] = error_analyze;
	analyze[A_IONUMBER][P_DSEMI] = error_analyze;
	analyze[A_IONUMBER][P_SEMICOLON] =  error_analyze;
	analyze[A_IONUMBER][P_DLESSDASH] = redirect_analyze;
	analyze[A_IONUMBER][P_DLESS] = redirect_analyze;
	analyze[A_IONUMBER][P_LESSGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_LESS] = redirect_analyze;
	analyze[A_IONUMBER][P_DGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_GREATAND] = redirect_analyze;
	analyze[A_IONUMBER][P_GREAT] =	redirect_analyze;
	analyze[A_IONUMBER][P_IONUMBER] = error_analyze;
	analyze[A_IONUMBER][P_ASSIGN] = error_analyze;
	analyze[A_IONUMBER][P_WORD] = cmd_analyze;
	analyze[A_IONUMBER][P_END] = end_analyze;
	// analyze[A_IOFILE][P_WORD] = cmd_analyze;
}

void init_redirect_analyze(t_anal analyze)
{
	analyze[A_REDIRECT][P_NEWLINE] = redirect_analyze;
	analyze[A_REDIRECT][P_ANDIF] = error_analyze;
	analyze[A_REDIRECT][P_AND] = error_analyze;
	analyze[A_REDIRECT][P_ORIF] = error_analyze;
	analyze[A_REDIRECT][P_PIPE] = redirect_analyze;
	analyze[A_REDIRECT][P_DSEMI] = error_analyze;
	analyze[A_REDIRECT][P_SEMICOLON] =  end_analyze;
	analyze[A_REDIRECT][P_DLESSDASH] = redirect_analyze;
	analyze[A_REDIRECT][P_DLESS] = redirect_analyze;
	analyze[A_REDIRECT][P_LESSGREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_LESS] = redirect_analyze;
	analyze[A_REDIRECT][P_DGREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_GREATAND] = redirect_analyze;
	analyze[A_REDIRECT][P_GREAT] =	redirect_analyze;
	analyze[A_REDIRECT][P_IONUMBER] = ionbr_analyze;
	analyze[A_REDIRECT][P_ASSIGN] = assign_analyze;
	analyze[A_REDIRECT][P_WORD] = cmd_analyze;
	analyze[A_REDIRECT][P_END] = end_analyze;
}

void init_end_analyze(t_anal analyze)
{
	analyze[A_END][P_NEWLINE] = end_analyze;
	analyze[A_END][P_ANDIF] = separator_analyze;
	analyze[A_END][P_AND] = separator_analyze;
	analyze[A_END][P_PIPE] = redirect_analyze;
	analyze[A_END][P_ORIF] = separator_analyze;
	analyze[A_END][P_DSEMI] = error_analyze;
	analyze[A_END][P_SEMICOLON] = separator_analyze;
	analyze[A_END][P_DLESSDASH] = redirect_analyze;
	analyze[A_END][P_DLESS] = redirect_analyze;
	analyze[A_END][P_LESSGREAT] = redirect_analyze;
	analyze[A_END][P_LESS] = redirect_analyze;
	analyze[A_END][P_DGREAT] = redirect_analyze;
	analyze[A_END][P_GREATAND] = redirect_analyze;
	analyze[A_END][P_GREAT] = redirect_analyze;
	analyze[A_END][P_IONUMBER] = ionbr_analyze;
	analyze[A_END][P_ASSIGN] = assign_analyze;
	analyze[A_END][P_WORD] = cmd_analyze;
	analyze[A_END][P_END] = end_analyze;
}

void	init_separator_analyze(t_anal analyze)
{
	analyze[A_SEPARATOR][P_NEWLINE] = separator_analyze;
	analyze[A_SEPARATOR][P_WORD] = cmd_analyze;
	analyze[A_SEPARATOR][P_AND] = separator_analyze;
	analyze[A_SEPARATOR][P_PIPE] = separator_analyze;
	analyze[A_SEPARATOR][P_GREAT] = end_analyze;
	analyze[A_SEPARATOR][P_GREATAND] = end_analyze;
	analyze[A_SEPARATOR][P_LESS] = end_analyze;
	analyze[A_SEPARATOR][P_LESSAND] = end_analyze;
	analyze[A_SEPARATOR][P_DGREAT] = end_analyze;
	analyze[A_SEPARATOR][P_DLESS] = end_analyze;
	analyze[A_SEPARATOR][P_DLESSDASH] = end_analyze;
	analyze[A_SEPARATOR][P_SEMICOLON] = separator_analyze;
	analyze[A_SEPARATOR][P_NEWLINE] = end_analyze;
	analyze[A_SEPARATOR][P_END] = end_analyze;
}

void init_start_analyze(t_anal analyze)
{
	// analyze[A_START][P_START] = separator_analyze;
	analyze[A_START][P_NEWLINE] = separator_analyze;
	analyze[A_START][P_ANDIF] = separator_analyze;
	analyze[A_START][P_AND] = separator_analyze;
	analyze[A_START][P_ORIF] = separator_analyze;
	analyze[A_START][P_PIPE] = redirect_analyze;
	analyze[A_START][P_DSEMI] = error_analyze;
	analyze[A_START][P_SEMICOLON] = separator_analyze;
	analyze[A_START][P_DLESSDASH] = redirect_analyze;
	analyze[A_START][P_DLESS] = redirect_analyze;
	analyze[A_START][P_LESSGREAT] = redirect_analyze;
	analyze[A_START][P_LESS] = redirect_analyze;
	analyze[A_START][P_DGREAT] = redirect_analyze;
	analyze[A_START][P_GREATAND] = redirect_analyze;
	analyze[A_START][P_GREAT] = redirect_analyze;
	analyze[A_START][P_IONUMBER] = ionbr_analyze;
	analyze[A_START][P_ASSIGN] = assign_analyze;
	analyze[A_START][P_WORD] = cmd_analyze;
	analyze[A_START][P_END] = end_analyze;
}

void init_word_analyze(t_anal analyze)
{
	analyze[A_WORD][P_NEWLINE] = separator_analyze;
	analyze[A_WORD][P_ANDIF] = separator_analyze;
	analyze[A_WORD][P_AND] = separator_analyze;
	analyze[A_WORD][P_ORIF] = separator_analyze;
	analyze[A_WORD][P_PIPE] = redirect_analyze;
	analyze[A_WORD][P_DSEMI] = error_analyze;
	analyze[A_WORD][P_SEMICOLON] = separator_analyze;
	analyze[A_WORD][P_DLESSDASH] = redirect_analyze;
	analyze[A_WORD][P_DLESS] = redirect_analyze;
	analyze[A_WORD][P_LESSGREAT] = redirect_analyze;
	analyze[A_WORD][P_LESS] = redirect_analyze;
	analyze[A_WORD][P_DGREAT] = redirect_analyze;
	analyze[A_WORD][P_GREATAND] = redirect_analyze;
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
	t_lst *tmp;

	tmp = NULL;
	if (!(analyzer = (t_analyzer*)malloc(sizeof(t_analyzer))))
		return (NULL);
	bzero_analyze(analyzer->analyze);
	init_process(&analyzer->process);
	init_redir(&analyzer->redir);
	init_job(&analyzer->job);
	init_start_analyze(analyzer->analyze);
	init_ionumber_analyze(analyzer->analyze);
	// init_assign_analyze(analyzer->analyze);
	init_word_analyze(analyzer->analyze);
	init_separator_analyze(analyzer->analyze);
	init_redirect_analyze(analyzer->analyze);
	init_end_analyze(analyzer->analyze);
	analyzer->state = A_START;
	analyzer->tok_state = P_START;
	analyzer->lexer = shell->lexer;
	analyzer->job_list = NULL;
	// analyzer->job_list = NULL;
	// ft_lstadd(&analyzer->job_list ,ft_lstnew(fetch_job(&analyzer->job), sizeof(t_job)));
	// ft_lstadd(&((t_job*)analyzer->job_list->content)->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
	// ft_lstadd(&(((t_process*)((t_job*)analyzer->job_list->content)->process_list->content)->redir_list), ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
	return (analyzer);
}
// ft_lstadd(&((t_process*)((t_job*)analyzer->job_list->content)->process_list->content)->redir_list ,
	// analyzer->process_list = NULL;
	// analyzer->redir_list = NULL;
	// analyzer->job_cmd = NULL;
	// analyzer->process_cmd = NULL;
	// analyzer->op[0] = NULL;
	// analyzer->op[1] = NULL;
	// analyzer->job_type = P_END;
	// analyzer->process_type = P_END;
	// init_create_job_analyze(analyzer->analyze);
	// analyzer->redir_type = P_END;
	// init_create_job_analyze(analyzer->analyze);
	// init_cmd_analyze(analyzer->analyze);
	// init_cmd_arg_analyze(analyzer->analyze);
	// init_create_job_analyze(analyzer->analyze)