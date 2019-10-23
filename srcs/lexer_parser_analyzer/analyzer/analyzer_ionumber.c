#include "sh42.h"

t_lst *redirect_analyze(t_analyzer *analyzer, t_lexer * lexer, t_job *job, t_lst *lst)
{
	ft_printf("REDIDIDIRECT   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)analyzer;
	(void)job;
	// job->redir->op[0] = ft_jointab(job->cmd);
	// job->redir->type = ((t_token*)lexer->tok->content)->id;
	analyzer->state = A_REDIRECT;
	// analyzer->state = A_REDIRECT;
	// if (((t_token*)lexer->tok->content)->id == P_GREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_TRUNC;
	// else if (((t_token*)lexer->tok->content)->id == P_DGREAT || ((t_token*)lexer->tok->content)->id == P_ANDDGREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_APPEND;

	return (lst);
	// else if (((t_token*)lexer->tok->content)->id == P_LESS)
	// 	analyzer->fd_flags = O_RDONLY;
	// else if (((t_token*)lexer->tok->content)->id == P_DLESSDASH || ((t_token*)lexer->tok->content)->id == P_DLESS)
		// analyzer->state = P_HEREDOC_REDIRECT;

	// delimite une list et determine la redirection IN ou OUT ou HERE_DOC
	// met dans la struct t_filedesc l'action IN OUT HERE_DOC...
	// depuis l'actual FD vers le wanted FD
}

t_lst *ionbr_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	ft_printf("IOOOOOOONBR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	(void)analyzer;
	// if (analyzer->state == A_WORD)
		// job->redir->op[0] = ft_jointab(job->cmd);
	// job->redir->op[0] = ft_strdup(((t_token*)lexer->tok->content)->data);
	// job->redir->ionumber = ft_atoi(((t_token*)lexer->tok->content)->data);
	// analyzer->state = A_REDIRECT;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence

	return (lst);
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
}