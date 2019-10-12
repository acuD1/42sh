#include "sh42.h"

void word_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	analyzer->state = A_WORD;
	(void)job;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// TANT QUE token word 
	// premier token word  = cmd 
	// le suivant = opt 
	// le reste = cmd data
}

void end_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("ENNNNNND   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	analyzer->state = A_END;
	(void)job;
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}	

void separator_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("SEPARARARTOR   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	analyzer->state = A_SEPARATOR;
	(void)job;
	// delimite le list de token en une list ou un job
}

void redirect_analyze(t_analyzer *analyzer, t_lexer * lexer, t_job *job)
{
	ft_printf("REDIDIDIRECT   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)job;
	analyzer->state = A_REDIRECT;
	// delimite une list et determine la redirection IN ou OUT ou HERE_DOC
	// met dans la struct t_filedesc l'action IN OUT HERE_DOC...
	// depuis l'actual FD vers le wanted FD
}

void error_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("EROROORRR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)job;
	// en theorie doit devalider la list de token et la flush
}

void ionbr_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("IOOOOOOONBR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)job;
	analyzer->state = A_IONUMBER;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
}

void assign_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)job;
	analyzer->state = A_ASSIGN;
	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}

// void start_analyze(t_analyzer *analyzer, t_job *job, t_lexer *lexer)
// {
// 	ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
// 	(void)job;
// 	analyzer->state = A_START;
// }

t_job	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lexer *lexer;
	t_job *job;
	t_lst **head;

	job = NULL;
	analyzer = NULL;
	lexer = shell->lexer;
	head = &lexer->tok;
	analyzer = init_analyze(analyzer);
	analyzer->state = A_START;
	if (parser(shell, lexer) != TRUE)
	{
		//erreur
		return (NULL); //shell->job = NULL;
	}
	while (analyzer->state != A_END && ft_strcmp("(null)", ((t_token*)lexer->tok->content)->data))
	{
		// ft_printf("WTFFFF  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)lexer->tok->content)->id](analyzer, lexer, job);
		lexer->tok = lexer->tok->next;
	}
	lexer->tok = *head;
	return (job);
}
