#include "sh42.h"

// char 		*exp_paren(t_token *tok, char *expansion, t_core *shell);
// {
// 	char *str;
// 	int index;

// 	str = NULL;
// 	index = 0;
// 	if (!ft_strncmp(exp, "$(", len))
// 	{
// 		index = lexer->buf_pos;
// 		while (&lexer->buff[index])
// 		{
// 			if (lexer->buff[index] == ')')
// 			{
// 				break; // CECI EST UN BUG
// 			}
// 			else
// 				index++;
// 			if (!lexer->buff[index + 1])
// 			{
// 				ft_dprintf(2, "cmdsubst>\n" );
// 				break;
// 				// lexer->buf_pos = index;
// 				// return (lexer_token);
// 				// subprompt("braceparam>");
// 			}
// 		}
// 		index++;
// 		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, index - lexer->buf_pos)))
// 			return (NULL);
// 		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
// 			return (NULL);
// 		free(str);
// 		lexer->ntok++;
// 		lexer->buf_pos = index;
// 	}
// 	return (lexer_token);
// }