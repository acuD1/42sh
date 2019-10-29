#include "sh42.h"

void ionbr_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("IONBR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// if (analyzer->state == A_WORD)
	// {
	// 	// analyzer->job.command = ft_jointab(analyzer->job.cmd);
	// 	analyzer->op[0] = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
	// 	analyzer->process_type = P_IONUMBER;
	// 	// analyzer->redir->ionumber = ft_atoi(((t_token*)lexer->tok->content)->data);
	// }
	// analyzer->state = A_REDIRECT;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
		(void)job;
	analyzer->state = A_IONUMBER;
}

void error_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("ERROR state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	analyzer->state = A_STOP;
	if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
		(void)job;
	// en theorie doit devalider la list de token et la flush
}

void assign_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("ASSIGN state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
		(void)job;
	analyzer->state = A_ASSIGN;
	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}