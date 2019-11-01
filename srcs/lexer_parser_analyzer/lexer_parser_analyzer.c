#include "sh42.h"

void lexer_parser_analyzer(t_core *shell, char *line)
{

	shell->lexer = lexer(line);
	if (parser(shell->lexer) == TRUE)
	{
		 analyzer(shell);
		// if (shell->job_list)
		// 	ft_printjoblst(shell->job_list);
		// if (shell->assign_list)
		// {
		// 	ft_printf("============= ASSIGN ============\n");
		// 	ft_printassignlist(shell->assign_list);
		// }
	}
	else
		ft_printf("error parser, va savoir pourquoi...\n");
	//ft_freelexerlist(&shell->lexer);
	// free(lex);
}
