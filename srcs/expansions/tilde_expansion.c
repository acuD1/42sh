#include "sh42.h"

char 		*exp_tilde(t_token *tok, char *expansion, t_core *shell);
// {
// 	char *str;

// 	str = NULL;
// 	if ( == '~')
// 	{
// 		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len)))
// 			return (NULL);
// 		if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,id, str), sizeof(t_token)))))
// 			return (NULL);
// 		free(str);
// 		lexer->ntok++;
// 		lexer->buf_pos += len;
// 	}
// 	return (lexer_token);
// }