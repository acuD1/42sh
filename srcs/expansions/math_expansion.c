// #include "sh42.h"

// char 		*exp_hook(t_token *tok, char *expansion, t_core *shell)
// {
// 	char *str;
// 	int index;

// 	str = NULL;
// 	index = 0;
// 	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "$[", len))
// 	{
// 		index = lexer->buf_pos;
// 		while (&lexer->buff[index])
// 		{
// 			if (lexer->buff[index] == ']')
// 			{
// 				break; // CECI EST UN BUG
// 			}
// 			else
// 				index++;
// 			if (!lexer->buff[index + 1])
// 			{
// 				ft_dprintf(2, "mathsubst>\n" );
// 				// lexer->buf_pos = index;
// 				break;
// 				// subprompt("braceparam>");
// 			}
// 		}
// 		index += 2;
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

// char 		*exp_dbparen(t_token *tok, char *expansion, t_core *shell);
// {
// 	char *str;
// 	int index;

// 	str = NULL;
// 	index = 0;
// 	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "$((", len))
// 	{
// 		index = lexer->buf_pos;
// 		while (lexer->buff[index])
// 		{
// 			if (lexer->buff[index] == ')' && lexer->buff[index + 1]
// 			 && lexer->buff[index + 1] == ')')
// 			{
// 				break; // CECI EST UN BUG
// 			}
// 			else
// 				index++;
// 			if (!&lexer->buff[index + 1])
// 			{
// 				ft_dprintf(2, "mathsubst>\n" );
// 				break;
// 				// lexer->buf_pos = index;
// 				// return (lexer_token);
// 				// subprompt("braceparam>");
// 			}
// 		}
// 		index += 2;
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