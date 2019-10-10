/*
** AST
*/


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
