#include "sh42.h"

void expansion_analyze(t_analyzer *analyzer)
{
	char *tmp;

	ft_printf("EXPANSION state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	tmp = NULL;
	tmp = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer, 0);
	// if (((t_token*)analyzer->lexer->content)->id == P_DBPARENT)
	// 	tmp = arithmetique_expansion(analyzer);
	// else if (((t_token*)analyzer->lexer->content)->id == P_PARENT)
	// 	tmp = cmd_substitution_expansion(analyzer);
	// else if (((t_token*)analyzer->lexer->content)->id == P_BRACKET || ((t_token*)analyzer->lexer->content)->id == P_DOLLAR)
	// 	tmp = param_expansion(analyzer);
	// else if (((t_token*)analyzer->lexer->content)->id == P_TILDE)
	// 	tmp = path_expansion(analyzer);
	if (analyzer->state == A_START || analyzer->state == A_SEPARATOR)
		analyzer->process.av = fill_cmd_process(tmp);
	else if (analyzer->state == A_WORD)
		analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, tmp);
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_WORD;
	free(tmp);
}
