#include "sh42.h"

void init_redir(t_redir *new)
{
	new->op[0] = NULL;
	new->op[1] = NULL;
	new->type = P_START;
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

t_analyzer *redir_analyze(t_analyzer *analyzer, t_core *shell)
{
	// ft_dprintf(2, "CREATE REDIR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	ft_lstappend(&analyzer->redir_list, ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
	init_redir(&analyzer->redir); //free op[2]
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_WORD;
	(void)shell;
	return (analyzer);
}

t_analyzer *redirect_analyze(t_analyzer *analyzer, t_core *shell)
{
	// ft_dprintf(2, "REDIRECT state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer, 1);
	analyzer->redir.type = ((t_token*)analyzer->lexer->content)->id;
	analyzer->state = A_REDIRECT;
	(void)shell;
	return (analyzer);
}
