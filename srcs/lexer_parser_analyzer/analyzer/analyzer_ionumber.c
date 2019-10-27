#include "sh42.h"

void redirect_analyze(t_analyzer *analyzer)
{
	ft_printf("REDIRECT state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// job->redir->op[0] = ft_jointab(job->cmd);
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

void ionbr_analyze(t_analyzer *analyzer)
{
	ft_printf("IONBR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	if (analyzer->state == A_WORD)
	{
		// analyzer->job.command = ft_jointab(analyzer->job.cmd);
		analyzer->redir.op[0] = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
		// analyzer->redir->ionumber = ft_atoi(((t_token*)lexer->tok->content)->data);
	}
	// analyzer->state = A_REDIRECT;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
	analyzer->state = A_IONUMBER;
}

void error_analyze(t_analyzer *analyzer)
{
	ft_printf("ERROR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->state = A_STOP;
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	// en theorie doit devalider la list de token et la flush
}

void assign_analyze(t_analyzer *analyzer)
{
	ft_printf("ASSIGN state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->state = A_ASSIGN;
	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}