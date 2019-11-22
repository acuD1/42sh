#include "sh42.h"

char *tilde_expansion(char *str, t_core *shell)
{
	t_db *db_tmp;

	db_tmp = NULL;
	if (ft_strcmp(str, "~"))
		return (NULL);
	if (!(db_tmp = search_db(shell->env, "HOME")))
		return (NULL);
	else
		return (db_tmp->value);
	// ft_dprintf(2, "PARAM EXP state %s    %s %s\n", str , &str[1], db_tmp->value);
}

char *param_expansion(t_token *token, t_core *shell)
{
	t_db *db_tmp;
	char *tmp;
	int i;

	i = ft_strlen(token->data);
	tmp = NULL;
	db_tmp = NULL;
	if (token->id == P_BRACKET)
		tmp = ft_strsub(token->data, 2, i - 3);
	else if (token->id == P_DOLLAR)
		tmp = ft_strsub(token->data, 1, i - 1);
	if (!(db_tmp = search_db(shell->env, tmp)))
	{
		free(tmp);
		return (NULL);
	}
	else
	{
		free(tmp);
		return (db_tmp->value);
	}
}

// uint8_t exp_dispatcher(analyzer, shell)
// {

// }

t_analyzer *expansion_analyze(t_analyzer *analyzer, t_core *shell)
{
	char *tmp;

	tmp = NULL;
	analyzer->job.command = fill_cmd_job(analyzer, 1);
	ft_dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "EXPANSION state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	// if (((t_token*)analyzer->lexer->content)->id == P_DBPARENT || ((t_token*)analyzer->lexer->content)->id == P_HOOK)
	// {
	// 	if ((tmp = arithmetique_expansion(((t_token*)analyzer->lexer->content), shell)))
	// 	{
	// 		free(((t_token*)analyzer->lexer->content)->data);
	// 		((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);
	// 	}
	// 	analyzer->state = A_WORD;
	// 	cmd_analyze(analyzer, shell);
	// 	return (analyzer);
	// }
	// if (((t_token*)analyzer->lexer->content)->id == P_PARENT)
	// {
	// 	if ((tmp = cmd_substitution_expansion(((t_token*)analyzer->lexer->content), shell)))
	// 	{
	// 		free(((t_token*)analyzer->lexer->content)->data);
	// 		((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);
	// 	}
	// 	analyzer->state = A_WORD;
	// 	return (cmd_analyze(analyzer, shell));
	// 	// return (analyzer);
	// }
	// else if (((t_token*)analyzer->lexer->content)->id == P_BRACKET || ((t_token*)analyzer->lexer->content)->id == P_DOLLAR)
	// {
	// 	if ((tmp = param_expansion(((t_token*)analyzer->lexer->content), shell)))
	// 	{
	// 		free(((t_token*)analyzer->lexer->content)->data);
	// 		((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);	
	// 	}
	// 	analyzer->state = A_WORD;
	// 	cmd_analyze(analyzer, shell);
	// 	return (analyzer);
	// }
	if (((t_token*)analyzer->lexer->content)->id == P_TILDE)
	{
		if ((tmp = tilde_expansion(((t_token*)analyzer->lexer->content)->data, shell)))
		{
			free(((t_token*)analyzer->lexer->content)->data);
			((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);
		}
		analyzer->state = A_WORD;
		return (analyzer = cmd_analyze(analyzer, shell));
	}
	return (analyzer);
}
