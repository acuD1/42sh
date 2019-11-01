// char *ft_jointab(char **tablo)
// {
// 	char *str;
// 	int j;
// 	int i;

// 	j = 0;
// 	i = ft_tablen(tablo);
// 	if (!(str = ft_strnew(0)) || !tablo)
// 		return (NULL);
// 	while (tablo[j] && j < i)
// 	{
// 		str = ft_strjoinf(str, tablo[j], 1);
// 		if (tablo[j + 1])
// 			str = ft_strjoinf(str, " ", 1);
// 		j++;
// 	}
// 	return(str);
// }
// t_lst	*ft_create_token(char *data, e_parser_state opeid)
// {
// 	t_lst		*new;
// 	t_token		*tok;

// 	tok = NULL;
// 	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
// 		return (NULL);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!(tok = (t_token*)malloc(sizeof(t_token))))
// 		return (NULL);
// 	new->content = (void*)fetch_lexer_token(tok, opeid, data);
// 	return (new);
// }


/*
** CREE LES TOKENS LEXER 
*/

// t_lst			*ft_add_token(t_lst **curr, e_parser_state opeid, char *data)
// {
// 	t_lst		*tmp;
// 	t_lst		*new;

// 	if (!(*curr))
// 		return (*curr = ft_create_token(data, opeid));
// 	if ((*curr)->next)
// 	{
// 		new = (*curr);
// 		while (new->next)
// 			new = new->next;
// 		tmp = ft_create_token(data, opeid);
// 		tmp->prev = new;
// 		tmp->next = NULL;
// 		new->next = tmp;
// 	}
// 	else
// 	{
// 		tmp = *curr;
// 		tmp->next = ft_create_token(data, opeid);
// 		tmp->next->prev = tmp;
// 	}
// 	return (*curr);
// }

// t_lst			*ft_lstadd(t_lst **curr, t_lst *new)
// {
// 	t_lst		*tmp;

// 	if (!(*curr))
// 		return (*curr = new);
// 	if ((*curr)->next)
// 	{
// 		tmp = (*curr);
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		new->prev = tmp;
// 		new->next = NULL;
// 		tmp->next = new;
// 	}
// 	else
// 	{
// 		tmp = *curr;
// 		tmp->next = new;
// 		new->prev = tmp;
// 		new->next = NULL;

// 	}
// 	return (*curr);
// }
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

	// ft_lstappend(&analyzer->job_list ,ft_lstnew(fetch_job(&analyzer->job), sizeof(t_job)));

	// ft_lstadd(&((t_job*)analyzer->job_list->content)->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));

	// ft_lstadd(&(((t_process*)((t_job*)analyzer->job_list->content)->process_list->content)->redir_list), ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
// ft_lstadd(&((t_process*)((t_job*)analyzer->job_list->content)->process_list->content)->redir_list ,
	// analyzer->process_list = NULL;
	// analyzer->redir_list = NULL;
	// analyzer->job_cmd = NULL;
	// analyzer->process_cmd = NULL;
	// analyzer->op[0] = NULL;
	// analyzer->op[1] = NULL;
	// analyzer->job_type = P_END;
	// analyzer->process_type = P_END;
	// init_create_job_analyze(analyzer->analyze);
	// analyzer->redir_type = P_END;
	// init_create_job_analyze(analyzer->analyze);
	// init_cmd_analyze(analyzer->analyze);
	// init_cmd_arg_analyze(analyzer->analyze);
	// init_create_job_analyze(analyzer->analyze)

// t_lst *ft_create_job(char *cmd, e_parser_state id, t_lst *list);
// t_lst *ft_create_redir(char *op[2], e_parser_state id)
// {
// 	t_lst		*new;
// 	t_redir 	*redir;

// 	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
// 		return (NULL);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!(redir = (t_redir*)malloc(sizeof(t_redir))))
// 		return (NULL);
// 	redir->op[0] = op[0];
// 	redir->op[1] = op[1];
// 	redir->type = id;
// 	new->content = (void*)fetch_redir(redir);
// 	return (new);
// }
// t_lst *ft_create_process(char **cmd, e_parser_state id, t_lst *list);

// t_lst *ft_create_redir(char *op[2], e_parser_state id);


// void init_cmd_analyze(t_anal analyze)
// {
// 	analyze[A_CMD][P_NEWLINE] = separator_analyze;
// 	analyze[A_CMD][P_ANDIF] = redirect_analyze;
// 	analyze[A_CMD][P_AND] = redirect_analyze;
// 	analyze[A_CMD][P_ORIF] = redirect_analyze;
// 	analyze[A_CMD][P_PIPE] = redirect_analyze;
// 	analyze[A_CMD][P_DSEMI] = separator_analyze;
// 	analyze[A_CMD][P_SEMICOLON] = separator_analyze;
// 	analyze[A_CMD][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CMD][P_DLESS] = redirect_analyze;
// 	analyze[A_CMD][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CMD][P_LESS] = redirect_analyze;
// 	analyze[A_CMD][P_DGREAT] = redirect_analyze;
// 	analyze[A_CMD][P_GREATAND] = redirect_analyze;
// 	analyze[A_CMD][P_GREAT] = redirect_analyze;
// 	analyze[A_CMD][P_IONUMBER] = ionbr_analyze;
// 	analyze[A_CMD][P_ASSIGN] = assign_analyze;
// 	analyze[A_CMD][P_WORD] = cmd_analyze;
// 	analyze[A_CMD][P_END] = end_analyze;
// }

// void init_cmd_arg_analyze(t_anal analyze)
// {
// 	analyze[A_CMD_ARG][P_NEWLINE] = separator_analyze;
// 	analyze[A_CMD_ARG][P_ANDIF] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_AND] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_ORIF] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_PIPE] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DSEMI] = separator_analyze;
// 	analyze[A_CMD_ARG][P_SEMICOLON] = separator_analyze;
// 	analyze[A_CMD_ARG][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DLESS] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_LESS] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_DGREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_GREATAND] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_GREAT] = redirect_analyze;
// 	analyze[A_CMD_ARG][P_IONUMBER] = ionbr_analyze;
// 	analyze[A_CMD_ARG][P_ASSIGN] = assign_analyze;
// 	analyze[A_CMD_ARG][P_WORD] = cmd_analyze;
// 	analyze[A_CMD_ARG][P_END] = end_analyze;
// }



// void init_create_redir_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_REDIR][P_NEWLINE] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_ANDIF] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_AND] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_ORIF] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_PIPE] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_DSEMI] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_SEMICOLON] =  error_analyze;
// 	analyze[A_CREATE_REDIR][P_DLESSDASH] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_DLESS] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_LESSGREAT] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_LESS] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_DGREAT] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_GREATAND] = redir_analyze;
// 	analyze[A_CREATE_REDIR][P_GREAT] =	redir_analyze;
// 	analyze[A_CREATE_REDIR][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_REDIR][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_REDIR][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_REDIR][P_END] = separator_analyze;
// }

// void init_create_separator_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_PROCESS][P_NEWLINE] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_ANDIF] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_AND] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_ORIF] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_PIPE] = separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_DSEMI] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_SEMICOLON] =  separator_analyze;
// 	analyze[A_CREATE_PROCESS][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_DLESS] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_LESS] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_DGREAT] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_GREATAND] = redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_GREAT] =	redirect_analyze;
// 	analyze[A_CREATE_PROCESS][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_PROCESS][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_PROCESS][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_PROCESS][P_END] = separator_analyze;
// }

// void init_create_job_analyze(t_anal analyze)
// {
// 	analyze[A_CREATE_JOB][P_NEWLINE] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_ANDIF] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_AND] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_ORIF] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_PIPE] = separator_analyze;
// 	analyze[A_CREATE_JOB][P_DSEMI] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_SEMICOLON] =  separator_analyze;
// 	analyze[A_CREATE_JOB][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_DLESS] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_LESS] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_DGREAT] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_GREATAND] = redirect_analyze;
// 	analyze[A_CREATE_JOB][P_GREAT] =	redirect_analyze;
// 	analyze[A_CREATE_JOB][P_IONUMBER] = error_analyze;
// 	analyze[A_CREATE_JOB][P_ASSIGN] = assign_analyze;
// 	analyze[A_CREATE_JOB][P_WORD] = cmd_analyze;
// 	analyze[A_CREATE_JOB][P_END] = end_analyze;
// }




// if (analyzer->state == A_WORD)
	// {
		// ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// 	// ft_printf("gmreangj  %s %s \n", ((t_job*)(lst->jobs->content))->cmd[0], job->redir->op[1]);
	// 	job = init_job();
	// 	// ft_printf("BKABKAAJ  %s %s \n", ((t_job*)(lst->jobs->content))->cmd[0], job->redir->op[1]);
	// 	// lst->jobs = lst->jobs->next;
	// }
	// if (analyzer->lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
	// {
	// 	lst = ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// 	job = init_job();
	// 	analyzer->state = A_STOP;
	// 	lst = lst->next;
	// 	printf("NIDSQFNIN\n");
	// }
	// if (((t_token*)lexer->tok->content)->id == 4 || ((t_token*)lexer->tok->content)->id == 8)
	// {
	// 	lst = ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// 	printf("gfgrehwgerg\n");
	// 	job = init_job();
	// 	lst = lst->next;
	// 	analyzer->state = A_END;
	// 	// job = init_job();
	// if (!analyzer->lexer->tok->next->next)
		// analyzer->state = A_STOP;
		// lst = lst->next;
	// }

// printf("DEBUG\n");
	// ft_printjob(&analyzer->job);
	// ft_printprocess(&analyzer->process);
	// ft_printredir(&analyzer->redir);
	// ft_lstappend(&ret, ft_lstnew(fetch_job(job), sizeof(t_job)));
	// printlstjob(ret);
	// ft_printjobcmd(job, 0);
	//flush lexer
			// printanalyzer(analyzer);
			// ((t_process*)analyzer->job_list->content)->process_list = ft_lstappend(&analyzer->job_list->content->process_list, ft_lstnew(fetch_process(&analyzer->process), sizeof(t_process)));
			// ((t_redir*)analyzer->job_list->content->process_list->content)->ection = ft_lstappend(&analyzer->job_list->content->process_list->content->ection, ft_lstnew(fetch_redir(&analyzer->redir), sizeof(t_redir)));
			// ft_printjob(((t_job*)analyzer->job_list->content));
			// ft_printprocess(((t_process*)&analyzer->job_list->content->process_list->content));
			// ft_printredir(((t_redir*)&analyzer->process_list->content->ection->content));


	// if (analyzer->process.av)
	// analyzer->job.command = getjoblistcmdtab(analyzer->job.process_list);
	// ft_printf("strp %s\n", analyzer->job.command);
	// init_job(&analyzer->job);
		// process_analyze(analyzer);

// t_lst *ft_create_process(char **cmd, e_parser_state id, t_lst *list)
// {
// 	t_lst		*new;
// 	t_process *process;

// 	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
// 		return (NULL);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!(process = (t_process*)malloc(sizeof(t_process))))
// 		return (NULL);
// 	process->av = cmd;
// 	process->type = id;
// 	process->redir_list = list;
// 	new->content = (void*)fetch_process(process);
// 	return (new);
// }


// void free_analyze(t_analyzer *analyzer)
// {
// 	t_lst *tmp;

// 	tmp = analyzer->redir_list;
// 	while (tmp)
// 	{
// 		tmp = analyzer->redir_list->next;
// 		ft_free_redir((t_redir*)analyzer->redir_list->content);
// 		free(analyzer->redir_list);
// 	}
// 	tmp = analyzer->process_list;
// 	while (tmp)
// 	{
// 		tmp = analyzer->process_list->next;
// 		ft_free_processlist(&analyzer->process_list);
// 		free(analyzer->process_list);
// 	}
// 	if (analyzer->job_cmd)
// 		free(analyzer->job_cmd);
// 	if (*analyzer->process_cmd)
// 		ft_tabfree(analyzer->process_cmd);
// 	if (*analyzer->op)
// 	{
// 		free(&analyzer->op[0]);
// 		free(&analyzer->op[1]);
// 	}
// }

// int ft_tablen(char **tb)
// {
// 	int i;

// 	i = 0;
// 	if (!tb)
// 		return (0);
// 	while (tb[i])
// 		i++;
// 	return (i);
// }

// void start_analyze(t_analyzer *analyzer, t_job *job, t_lst *lst, t_lexer *lexer)
// {
// 	ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
// 	(void)job;
// 	analyzer->state = A_START;
// }


// t_lst *ft_create_job(char *cmd, e_parser_state id, t_lst *list)
// {
// 	t_lst		*new;
// 	t_job *job;

// 	job = NULL;
// 	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
// 		return (NULL);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!(job = (t_job*)malloc(sizeof(t_job))))
// 		return (NULL);
// 	job->type = id;
// 	job->process_list = list;
// 	job->command = cmd;
// 	new->content = (void*)fetch_job(job);
// 	return (new);
// }
// void cmd_arg_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
// {
// 	char **arg;
// 	int i;
// 	int j;

// 	arg = NULL;
// 	i = 0;
// 	j = 0;
// 	if (!job->cmd[0])
// 		return;
// 	else
// 	{
// 		i = ft_tablen(job->cmd);
// 		printf("I %d\n", i);
// 		if (!(arg = (char**)malloc(sizeof(char*) * i + 1)))
// 			return;
// 		while (j < i)
// 		{
// 			printf("J %s %d\n", job->cmd[j] ,j);
// 			arg[j] = ft_strcpy(arg[j], job->cmd[j]);
// 			j++;
// 		}
// 		// arg[j] = ft_strdup(((t_token*)lexer->tok->content)->data);
// 	}
// 	(void)analyzer;
// 	(void)lexer;
// }


// void fill_opzero_job(t_analyzer *analyzer, t_lexer * lexer, t_job *job)
// {
// 	if (((t_token*)lexer->tok->content)->id == P_IONUMBER)
// 	{
// 		job->redir->op[0] = ft_jointab(job->cmd);
// 		printf("JOBI JOBA '%s'\n", job->redir->op[0]);
// 	}
// 	(void)analyzer;
// 	(void)lexer;
	// else if (analyzer->state == IOHERE)
	// {

	// }
// }

/*
** AST
*/


// typedef struct  s_filedesc
// {
//     unsigned int        action;
//     int32_t             actual;
//     int32_t             wanted;
// }               t_filedesc; // RIP TOI


// b_node	*ast_add_node(b_node *root, b_node *left, b_node *right, e_ast_state nodetype, char *data);
// b_node	*ast_attach_node(b_node *root, b_node *leftnode, b_node *rightnode);
// void 	ast_delete(b_node *node);
// void error_ast(t_lexer *lexer);
// b_ast *init_ast(void);
// b_ast *ast(t_lexer *lexer);
// typedef struct s_ast 	b_ast;
// typedef struct s_node 	b_node;

// typedef void (*t_asting)(t_lexer*);
// typedef t_asting 	t_ast[NB_AST_STATE];


// typedef struct s_analyze
// {
// 	e_ast_state *machine;
// }				t_analyze;

// typedef struct s_ast
// {
// 	b_node 		*root;
// 	t_analyze 	*analyze[NB_AST_STATE];
// 	e_ast_state state;
// }				b_ast;

// typedef struct 	s_node
// {
// 	// b_node		*base;
//    	e_ast_state type;
//     char 		*data;
//     size_t 		data_len;
//     b_node		*left;
//     b_node		*right;
// } 				b_node;

// typedef enum ast_state
// {
// 	B_PROGRAM,
// 	B_COMPLETE_CMDS,
// 	B_COMPLETE_CMD,
// 	B_LIST,
// 	B_AND_OR,
// 	B_PIPE_SEQUENCE,
// 	B_CMD,
// 	// B_COMPOUND_CMD,
// 	B_SUBSHELL,
// 	// B_COMPOUND_LIST,
// 	// B_TERM,
// 	// B_FOR_CLAUSE,
// 	B_NAME,
// 	// B_IN,
// 	B_WORDLIST,
// 	// B_CASE_CLAUSE,
// 	// B_CASE_LISTS,
// 	// B_CASE_LIST,
// 	// B_CASE_ITEMS,
// 	// B_CASE_ITEM,
// 	// B_PATTERN,
// 	// B_IF_CLAUSE,
// 	// B_ELSE_PART,
// 	// B_WHILE_CLAUSE,
// 	// B_UNTIL_CLAUSE,
// 	// B_FCT_DEFINITION,
// 	// B_FCT_BODY,	
// 	// B_FNAME,
// 	// B_BRACE_GROUP,
// 	// B_DO_GROUP,
// 	B_SIMPLE_CMD,
// 	B_CMD_NAME,
// 	B_CMD_WORD,
// 	B_CMD_PREFIX,
// 	B_CMD_SUFFIX,
// 	B_REDIRECT_LIST,
// 	B_IO_REDIRECT,
// 	B_IO_FILE,
// 	B_FILENAME,
// 	B_IO_HERE,
// 	B_HERE_END,
// 	B_NEWLINE_LIST,
// 	B_LINEBREAK,
// 	B_SEPARATOR_OP,
// 	B_SEPARATOR,
// 	B_SEQUENTIAL_SEP,
// 	B_NEW,
// 	B_START,
// 	B_END,
// }			e_ast_state;



// b_node	*ast_add_node(b_node *root, b_node *left, b_node *right, e_ast_state nodetype, char *data)
// {
// 	b_node *new;

// 	if (!root)
// 		return (root = NULL);
// 	new = ast_attach_node(root, left, right);
// 	new->type = nodetype;
// 	new->data = ft_strdup(data);
// 	new->data_len = ft_strlen(data);
// 	return (new);
// }

// b_node	*ast_attach_node(b_node *root, b_node *leftnode, b_node *rightnode)
// {
// 	b_node *new;

// 	if (!root)
// 		return (NULL);
// 	if (!(new = (b_node*)malloc(sizeof(b_node))))
// 		return (NULL);
// 	new->left = leftnode;
// 	new->right = rightnode;
// 	new->type = B_NEW;
// 	new->data = NULL;
// 	new->data_len = 0;
// 	return (new);
// }

// void 	ast_delete(b_node *node)
// {
// 	if (node->data)
// 		free(node->data);
// 	if (node->right)
// 		ast_delete(node->right);
// 	if (node->left)
// 		ast_delete(node->left);
// }

// void error_ast(t_lexer *lexer)
// {
// 	ft_printf("ASTSTS   %u         %s\n", ((t_token*)lexer->tok->content)->id, ((t_token*)lexer->tok->content)->data);
// }


// // static void	bzero_ast(t_asting analyze)
// // {
// // 	int		index;

// // 	index = 0;
// // 	while (index < NB_AST_STATE)
// // 	{
// // 		analyze[index] = error_ast;
// // 		++index;
// // 	}
// // }

// b_ast *init_ast(void)
// {
// 	b_ast *ast;

// 	ast = NULL;
// 	if (!(ast = (b_ast*)malloc(sizeof(b_ast))))
// 		return (ast);
// 	ast->state = B_START;
// 	// bzero_ast(ast->analyze);
// 	// ast->root = 
// 	return (ast);
// }

// b_ast *ast(t_lexer *lexer)
// {
// 	b_ast *ast;

// 	if (!lexer || !lexer->tok)
// 		return (NULL);
// 	ast = init_ast();
// 	return (ast);
// }


// typedef enum 	tokenid
// {
// 	TOK_NEWLINE,    // \n
// 	TOK_ANDIF,        // &&
// 	TOK_AND,     // &
// 	TOK_ORIF,     // ||
// 	TOK_PIPE,       // |
// 	TOK_DSEMI,      // ;;
// 	TOK_SEMICOLON,        // ;
// 	TOK_DLESSDASH,  // <<-
// 	TOK_DLESS,      // <<
// 	TOK_LESSGREAT,  // <>
// 	TOK_LESSAND,    // <&
// 	TOK_LESS,       // <
// 	TOK_DGREAT,     // >>
// 	TOK_GREATAND,   // >&
// 	TOK_CLOBBER,    // >|
// 	TOK_GREAT,      // >
// 	TOKEN,          // NULL token
// 	TOK_IONUMBER,   // number juste before '>' or '<'
// 	TOK_ASSIGN,      // assignement_word stringwith an = final
// 	TOK_WORD,      // all others
// } e_tokenid;

// t_ast        *parser(t_core shell, t_parser *parser);


// #define NODETYPE(a) (a & (~NODE_DATA))   // get the type of the nodes

// typedef struct      quote
// {
//     char        *start;
//     size_t      lenstart;
//     char        *stop;
//     size_t      lenstop;
// } s_quote;

// struct s_quote    quotes[] =
//   {
//     {"\"", 1, "\"", 1},
//     {"'", 1, "'", 1},
//     {"`", 1, "`", 1},
//     {"${", 2, "}", 1},
//     {"$((", 2, "))", 2},
//     {"$(", 2, ")", 1},
//     {NULL, 0, NULL, 0},
//   };

// struct s_token quote[] =
// {
//     {TOKEN, NULL, 0},
//     {TOK_PARENT_OPEN, "(", 1},
//     {TOK_PARENT_CLOSE, ")", 1},
//     {TOK_BRACKET_OPEN, "{", 1},
//     {TOK_BRACKET_CLOSE, "}", 1},
//     {TOK_HOOK_OPEN, "[", 1},
//     {TOK_HOOK_CLOSE, "]", 1},
// };

// typedef enum    e_type
// {
//     E_DBQUOTE,
//     E_QUOTE,
//     E_PIPE,
//     E_PARENT_OPEN,
//     E_PARENT_CLOSE,
//     E_GREAT,
//     E_LESS,
//     E_SEMICOLON,
//     E_BACKQUOTE,
//     E_AND,
//     E_HOOK_OPEN,
//     E_HOOK_CLOSE,
//     E_BRACKET_OPEN,
//     E_BRACKET_CLOSE,
//     E_HASH,
//     E_PERCENT,
//     E_NEWLINE,
//     E_ANDIF,
//     E_ORIF,
//     E_DSEMI,
//     E_DLESS,
//     E_DGREAT,
//     E_LESSAND,
//     E_GREATAND,
//     E_LESSGREAT,
//     E_ANDDGREAT,
//     E_ANDGREAT,
//     E_DLESSDASH,
//     E_CLOBBER,
//     E_DEQ,
//     E_NOTEQ,
//     E_CASE,
//     E_DO,
//     E_DONE,
//     E_ELIF,
//     E_ELSE,
//     E_ESAC,
//     E_FI,
//     E_FOR,
//     E_IF,
//     E_IN,
//     E_THEN,
//     E_UNTIL,
//     E_WHILE,
//     E_IONUMBER,
//     E_ASSIGN,
//     E_WORD,
//     E_SPSTRING,
//     E_END,
//     E_ERROR,
//     E_START,
// }               t_type;

// static void ft_init_machine(t_machine *machine)
// {
//  machine[0] = E_DEFAULT;
//  machine[1] = E_END;
//  machine[2] = E_NEWLINE;
//  machine[3] = E_ANDIF;
//  machine[4] = E_AND;
//  machine[5] = E_ORIF;
//  machine[6] = E_PIPE;
//  machine[7] = E_DSEMI;
//  machine[9] = E_SEMICOLON;
//  machine[10] = E_PARENT_OPEN;
//  machine[11] = E_PARENT_CLOSE;
//  machine[12] = E_BRACKET_OPEN;
//  machine[13] = E_BRACKET_CLOSE;
//  machine[14] = E_HOOK_OPEN;
//  machine[15] = E_HOOK_OPEN;
//  ft_init_machine_bis(machine);
// }

// static void ft_init_machine_bis(t_machine *machine)
// {
//  machine[16] = E_DLESSDASH;
//  machine[17] = E_DLESS;
//  machine[18] = E_LESSGREAT;
//  machine[19] = E_LESSAND;
//  machine[20] = E_LESS;
//  machine[21] = E_DGREATt;
//  machine[22] = E_GREATAND;
//  machine[23] = E_CLOBBER;
//  machine[24] = E_GREAT;
//  machine[25] = E_DBQUOTE;
//  machine[26] = E_QUOTE;
//  machine[27] = E_BQUOTE;
//  machine[28] = E_IONUMBER;
//  machine[29] = E_ASSIGN;
//  machine[30] = E_WORD;
//  machine[31] = E_ERROR;
// }

// machine[TOK_NEWLINE] = E_NEWLINE;
// machine[TOK_EOF] = E_END;
// machine[TOK_ANDIF] = E_ANDIF;
// machine[TOK_AND] = E_AND;
// machine[TOK_ORIF] = E_ORIF;
// machine[TOK_PIPE] = E_PIRE;
// machine[TOK_DSEMI] = E_DSEMI;
// machine[TOK_SEMICOLON] = E_SEMICOLON;
// machine[TOK_PARENT_OPEN] = E_PARENT_OPEN
// machine[TOK_PARENT_CLOSE] = E_PARENT_CLOSE
// machine[TOK_BRACKET_OPEN] = E_BRACKET_OPEN
// machine[TOK_BRACKET_CLOSE] = E_BRACKET_CLOSE
// machine[TOK_HOOK_OPEN] = E_HOOK_OPEN
// machine[TOK_HOOK_OPEN] = E_HOOK_OPEN
// machine[TOK_DLESSDASH] = E_DLESSDASH;
// machine[TOK_DLESS] = E_DLESS;
// machine[TOK_LESSGREAT] = E_LESSGREAT;
// machine[TOK_LESSAND] = E_LESSAND;
// machine[TOK_LESS] = E_LESS;
// machine[TOK_DGREAT] = E_DGREATt;
// machine[TOK_GREATAND] = E_GREATAND;
// machine[TOK_CLOBBER] = E_CLOBBER;
// machine[TOK_GREAT] = E_GREAT;
// machine[TOK_DBQUOTE] = E_DBQUOTE;
// machine[TOK_QUOTE] = E_QUOTE;
// machine[TOK_BQUOTE] = E_BQUOTE;
// machine[TOK_IONUMBER] = E_IONUMBER;
// machine[TOK_ASSIGN] = E_ASSIGN;
// machine[TOK_WORD] = E_WORD;
// machine[TOK_WORD] = E_END;
// machine[TOK_ERROR] = E_ERROR;


// # define TOKEN                   NULL            
// # define T_ESCSEQ                "\\"
// # define T_EOF                   "EOF"
// # define T_DBQUOTE               "\""
// # define T_PIPE                  "|"
// # define T_LPARENT           "("
// # define T_RPARENT           ")"
// # define T_GREAT                 ">"
// # define T_LESS                  "<"
// # define T_SEMI              ";"
// # define T_BQUOTE                "`"
// # define T_AND                   "&"
// # define T_LHOOK             "{"
// # define T_RHOOK             "}"
// # define T_LBRACKET          "["
// # define T_RBRACKET          "]"
// # define T_HASH                  "#"
// # define T_PERCENT               "%"
// # define T_NEWLINE               "\\n"
// # define T_ANDIF                 "&&"
// # define T_ORIF                  "||"
// # define T_DSEMI                 ";;"
// # define T_DLESS                 "<<"
// # define T_DGREAT                    ">>"
// # define T_LESSAND               "<&"
// # define T_GREATAND              ">&"
// # define T_LESSGREAT             "<>"
// # define T_ANDDGREAT             "&>>"
// # define T_ANDGREAT              "&>"
// # define T_DLESSDASH             "<<-"
// # define T_CLOBBER               ">|"
// # define T_DEQ                   "=="
// # define T_NOTEQ                 "!="
// # define TOK_CASE                    "case"
// # define TOK_DO                      "do"
// # define TOK_DONE                    "done"
// # define TOK_ELIF                    "elif"
// # define TOK_ELSE                    "else"
// # define TOK_ESAC                    "esac"
// # define TOK_FI                      "fi"
// # define TOK_FOR                 "for"
// # define TOK_IF                      "if"
// # define TOK_IN                      "in"
// # define TOK_THEN                    "then"
// # define TOK_UNTIL                   "until"
// # define TOK_WHILE                   "while"
// # define TOK_IO_NUMBER               "IO number"
// # define TOK_ASSIGN                  "assign (=)"
// # define TOK_STRING                  "word"
// # define TOK_SPSTRING                "spword"
// # define TOK_END                 "end"
// # define TOK_ERROR                   "ERROR"
// # define TOK_START                   "START"



// machine[TOK_NEWLINE] = token_newline;
// machine[TOK_EOF] = token_eof;
// machine[TOK_ANDIF] = token_andif;
// machine[TOK_AND] = token_and;
// machine[TOK_ORIF] = token_orif;
// machine[TOK_PIPE] = token_pipe;
// machine[TOK_DSEMI] = token_dsemi;
// machine[TOK_SEMICOLON] = token_semicolon;
// machine[TOK_PARENT_OPEN] = token_lparent;
// machine[TOK_PARENT_CLOSE] = token_rparent;
// machine[TOK_BRACKET_OPEN] = token_lbracket;
// machine[TOK_BRACKET_CLOSE] = token_rbracket;
// machine[TOK_HOOK_OPEN] = token_lhook;
// machine[TOK_HOOK_OPEN] = token_rhook;
// machine[TOK_DLESSDASH] = token_dlessdash;
// machine[TOK_DLESS] = token_dless;
// machine[TOK_LESSGREAT] = token_lessgreat;
// machine[TOK_LESSAND] = token_lessand;
// machine[TOK_LESS] = token_less;
// machine[TOK_DGREAT] = token_dgreat;
// machine[TOK_GREATAND] = token_greatand;
// machine[TOK_CLOBBER] = token_clobber;
// machine[TOK_GREAT] = token_great;
// machine[TOK_DBQUOTE] = token_dbquote;
// machine[TOK_QUOTE] = token_quote;
// machine[TOK_BQUOTE] = token_bquote;
// machine[TOK_IONUMBER] = token_ionumber;
// machine[TOK_ASSWD] = token_assignement_word;
// machine[TOK_WORD] = token_word;
