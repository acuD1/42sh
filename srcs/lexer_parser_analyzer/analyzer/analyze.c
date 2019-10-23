#include "sh42.h"

t_lst *separator_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	ft_printf("SEPARARARTOR   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	analyzer->state = A_SEPARATOR;
	(void)job;
	// if (analyzer->state == A_WORD)
	// {
	// 	ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// 	// ft_printf("gmreangj  %s %s \n", ((t_job*)(lst->jobs->content))->cmd[0], job->redir->op[1]);
	// 	job = init_job();
	// 	// ft_printf("BKABKAAJ  %s %s \n", ((t_job*)(lst->jobs->content))->cmd[0], job->redir->op[1]);
	// 	// lst->jobs = lst->jobs->next;
	// }
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
	{
		lst = ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
		job = init_job();
		analyzer->state = A_STOP;
		lst = lst->next;
		printf("NIDSQFNIN\n");
	}
	if (((t_token*)lexer->tok->content)->id == 4 || ((t_token*)lexer->tok->content)->id == 8)
	{
		lst = ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
		printf("gfgrehwgerg\n");
		job = init_job();
		lst = lst->next;
		analyzer->state = A_END;
		// job = init_job();
		// lst = lst->next;
	}
	// delimite le list de token en une list ou un job
	return (lst);
}

t_lst *error_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	ft_printf("EROROORRR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_ERROR;
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	return (lst);
	// en theorie doit devalider la list de token et la flush
}

t_lst *assign_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	// ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_ASSIGN;
	return (lst);
	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}

t_lst	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lexer *lexer;
	t_job *job;
	t_lst *ret;
	t_lst **head;

	ret = NULL;
	job = NULL;
	analyzer = NULL;
	if (!shell->lexer)
		return (NULL);
	lexer = shell->lexer;
	analyzer = init_analyze(analyzer);
	job = init_job(); // new_job
	if (parser(shell, lexer) != TRUE)
	{
		//erreur
		return (ret); //shell->job = NULL;
	}
	//clean parser struct
	// while (analyzer->state != A_STOP)
	head = &ret;
	while (analyzer->state != A_STOP && (((t_token*)lexer->tok->next->content)->id != 24))
	{
		ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)lexer->tok->content)->id ,((t_token*)lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)lexer->tok->content)->id](analyzer, lexer, job, ret);
		lexer->tok = lexer->tok->next; // faire une fct get_token qui passe au token suivant ??
	}
	// ft_lstappend(&ret, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// job = init_job();
	// ret = *head;	
	printlstjob(ret);
	// ft_printjobcmd(job, 0);
	//flush lexer
	return (ret);
}
