
#include "sh42.h"

// char 		*exp_bracket(t_token *tok, char *expansion, t_core *shell);
// {
// 	char *str;
// 	int index;

// 	index = 0;
// 	str = NULL;

// 	if (!ft_strncmp(&lexer->buff[lexer->buf_pos], "${", len))
// 	{
// 		index = lexer->buf_pos;
// 		while (&lexer->buff[index])
// 		{
// 			if (lexer->buff[index] == '}')
// 			{
// 				break; // CECI EST UN BUG
// 			}
// 			else
// 				index++;
// 			if (!lexer->buff[index + 1])
// 			{
// 				ft_dprintf(2, "braceparam>\n" );
// 				// lexer->buf_pos = index;
// 				// return (lexer_token);
// 				break;
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

// char 		*exp_dollar(t_token *tok, char *expansion, t_core *shell);
// {
// 	char *str;
// 	int index;

// 	index = lexer->buf_pos + len;
// 	str = NULL;
// 	(void)len;
// 	if (lexer->buff[lexer->buf_pos] == '$')
// 	{
// 		while (lexer->buff[index])
// 		{
// 			if (lexer->buff[index] == '_' || ft_isdigit(lexer->buff[index]) || ft_isalpha(lexer->buff[index]))
// 				index++;
// 			else
// 			{
// 				// lexer->buf_pos++;
// 				// return (lexer_token);
// 				break;
// 			}
// 		}
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

