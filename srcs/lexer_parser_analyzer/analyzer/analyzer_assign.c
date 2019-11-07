#include "sh42.h"

void init_assign(t_db *db)
{
	db->key = NULL;
	db->value = NULL;
}

t_db *fetch_assign(t_db *assign)
{
	t_db *new;

	if (!assign)
		return (NULL);
	new = assign;
	if (assign->key)
		new->key = assign->key;
	else
		new->key = NULL;
	if (assign->value)
		new->value = assign->value;
	else
		new->value = NULL;
	return (new);

}

t_analyzer *ass_analyze(t_analyzer *analyzer, t_core *shell)
{
	// if (!analyzer->process.av[0])
		ft_lstappend(&analyzer->assign_list, ft_lstnew(fetch_assign(&analyzer->db), sizeof(t_db)));
	// else
		// ft_lstappend(&analyzer->process.assign_list, ft_lstnew(fetch_assign(&analyzer->db), sizeof(t_db)));
	// if (((t_kone*)analyzer->lexer->next->content)->id == P_WORD)
	//module assign qui check si existe et possible
	init_assign(&analyzer->db);
	(void)shell;
	return (analyzer);
}

t_analyzer *assign_analyze(t_analyzer *analyzer, t_core *shell)
{
	ft_printf("ASSIGN state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer, 0);
	if (((t_token*)analyzer->lexer->content)->id == P_ASSIGN && ((analyzer->state != A_WORD) || analyzer->state != A_EXPANSION))
	{
		// if (!analyzer->db.key)
			analyzer->db.key = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		// else
			// analyzer->db.key = ft_strjoinf(analyzer->db.key ,((t_token*)analyzer->lexer->content)->data, 1);
		analyzer->process.type = ((t_token*)analyzer->lexer->content)->id;
		analyzer->state = A_ASSIGN;
	}
	else
	{
		analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, ((t_token*)analyzer->lexer->content)->data);
		analyzer->state = A_WORD;
	}
	(void)shell;
	return (analyzer);
}
