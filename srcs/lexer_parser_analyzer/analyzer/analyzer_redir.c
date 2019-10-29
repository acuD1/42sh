#include "sh42.h"

void init_redir(t_redir *new)
{
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_ERROR;
	// new->fds[0] = 0;
	// new->fds[1] = 0;
}

void ft_free_redir(t_redir *redir)
{
	if (*redir->op[0])
		free(redir->op[0]);
	if (*redir->op[1])
		free(redir->op[1]);
	free(redir);
}

t_redir *fetch_redir(t_redir *redir, char *op[2], e_parser_state type)
{
	redir->op[0] = op[0];
	redir->op[1] = op[1];
	redir->type = type;
	return (redir);
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
	new->content = (void*)fetch_redir(redir, &op[2], id);
	return (new);
}

void redir_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("CREATE REDIR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// ft_lstappend(&analyzer->redir_list, ft_lstnew(&redir, sizeof(t_redir)));
	// ft_lstadd(&analyzer->redir_list, ft_create_redir(&analyzer->op[2], analyzer->redir_type));
	// ft_printredir((t_redir*)analyzer->redir_list->content);
		// init_redir(&analyzer->redir);
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_START;
	(void)job;
	// free(redir);
}

void redirect_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("REDIRECT state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// job->redir->op[0] = ft_jointab(job->cmd);
	// analyzer->redir_type = ((t_token*)analyzer->lexer->tok->content)->id;
	analyzer->state = A_REDIRECT;
	(void)job;
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