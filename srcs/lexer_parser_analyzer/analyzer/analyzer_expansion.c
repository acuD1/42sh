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

	// ft_printf("PARAM EXP state %s    %s %s\n", str , &str[1], db_tmp->value);
}

char *param_expansion(char *str, t_core *shell)
{
	t_db *db_tmp;

	db_tmp = NULL;
	if (str[0] != '$')
		return (NULL);
	if (!(db_tmp = search_db(shell->env, &str[1])))
		return (NULL);
	else
		return (db_tmp->value);

	// ft_printf("PARAM EXP state %s    %s %s\n", str , &str[1], db_tmp->value);
}

t_analyzer *expansion_analyze(t_analyzer *analyzer, t_core *shell)
{
	char *tmp;

	ft_printf("EXPANSION state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	tmp = NULL;
	// tmp = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	// if (((t_token*)analyzer->lexer->content)->id == P_DBPARENT)
	// 	tmp = arithmetique_expansion(analyzer);
	// else if (((t_token*)analyzer->lexer->content)->id == P_PARENT)
		// tmp = cmd_substitution_expansion(analyzer);
	if (((t_token*)analyzer->lexer->content)->id == P_BRACKET || ((t_token*)analyzer->lexer->content)->id == P_DOLLAR)
	{
		if ((tmp = param_expansion(((t_token*)analyzer->lexer->content)->data, shell)))
		{
			free(((t_token*)analyzer->lexer->content)->data);
			((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);
		}
		else
			get_token(analyzer);
		analyzer->state = A_EXPANSION;
	}
	else if (((t_token*)analyzer->lexer->content)->id == P_TILDE)
	{
		tmp = tilde_expansion(((t_token*)analyzer->lexer->content)->data, shell);
		free(((t_token*)analyzer->lexer->content)->data);
		((t_token*)analyzer->lexer->content)->data = ft_strdup(tmp);
	}
	analyzer->job.command = fill_cmd_job(analyzer, 0);
	// analyzer->state = A_EXPANSION;
	if (analyzer->state == A_ASSIGN)
	{
		analyzer->db.value = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		ass_analyze(analyzer, shell);
		analyzer->state = A_START;
	}
	if (((t_token*)analyzer->lexer->next->content)->id == P_ASSIGN && analyzer->state != A_WORD)
	{
		analyzer->db.key = ft_strjoinf(tmp, "=", 1);
		analyzer->process.type = ((t_token*)analyzer->lexer->content)->id;
		analyzer->state = A_ASSIGN;
		get_token(analyzer);
	}
	// cmd_analyze(analyzer);
	return (analyzer);
}
