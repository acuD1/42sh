#include "sh42.h"

void init_redir(t_redir *new)
{
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
}

void ft_free_redir(t_redir *redir)
{
	free(redir->op[0]);
	free(redir->op[1]);
	free(redir);
}

t_redir *fetch_redir(t_redir *redir)
{
	t_redir *new;

	if (!redir)
		return (NULL);
	new = redir;
	if (redir->op[0])
		new->op[0] = redir->op[0];
	else
		new->op[0] = NULL;
	if (redir->op[1])
		new->op[1] = redir->op[1];
	else
		new->op[1] = NULL;
	new->type = redir->type;
	return (new);
}

t_lst *ft_create_redir(char *op[2], e_parser_state id)
{
	t_lst		*new;
	t_redir 	*redir;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!(redir = (t_redir*)malloc(sizeof(t_redir))))
		return (NULL);
	redir->op[0] = op[0];
	redir->op[1] = op[1];
	redir->type = id;
	new->content = (void*)fetch_redir(redir);
	return (new);
}

//(((t_process*)((t_job*)analyzer->job_list->content)->process_list->content)->redir_list)
void redir_analyze(t_analyzer *analyzer)
{
	ft_printf("CREATE REDIR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	ft_lstappend(&analyzer->redir_list, ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
	init_redir(&analyzer->redir); //free op[2]
	// ft_lstappend(&analyzer->redir_list, ft_lstnew(&redir, sizeof(t_redir)));
	// ft_lstadd(&analyzer->redir_list, ft_create_redir(&analyzer->op[2], analyzer->redir_type));
	// ft_printredir((t_redir*)analyzer->redir_list->content);
		// init_redir(&analyzer->redir);
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_WORD;
	// free(redir);
}

void redirect_analyze(t_analyzer *analyzer)
{

	ft_printf("REDIRECT state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer);
	analyzer->redir.type = ((t_token*)analyzer->lexer->tok->content)->id;
	analyzer->state = A_REDIRECT;
	// analyzer->state = A_REDIRECT;
	// if (((t_token*)lexer->tok->content)->id == P_GREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_TRUNC;
	// else if (((t_token*)lexer->tok->content)->id == P_DGREAT || ((t_token*)lexer->tok->content)->id == P_ANDDGREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_APPEND;

	// else if (((t_token*)lexer->tok->content)->id == P_LESS)
	// 	analyzer->fd_flags = O_RDONLY;
	// else if (((t_token*)lexer->tok->content)->id == P_DLESSDASH || ((t_token*)lexer->tok->content)->id == P_DLESS)
		// analyzer->state = P_HEREDOC_REDIRECT;

	// delimite une list et determine la redirection IN ou OUT ou HERE_DOC
	// met dans la struct t_filedesc l'action IN OUT HERE_DOC...
	// depuis l'actual FD vers le wanted FD
}