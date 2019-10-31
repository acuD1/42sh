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

void ass_analyze(t_analyzer *analyzer)
{
	ft_lstappend(&analyzer->assign_list, ft_lstnew(fetch_assign(&analyzer->db), sizeof(t_db)));
	init_assign(&analyzer->db);
	// process_analyze(analyzer); // ou discard ?
}

void assign_analyze(t_analyzer *analyzer)
{
	ft_printf("ASSIGN state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer);
	analyzer->db.key = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	analyzer->process.type = ((t_token*)analyzer->lexer->content)->id;
	analyzer->state = A_ASSIGN;
}