/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:33:23 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/26 16:33:25 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_word_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_NEWLINE, P_WORD, ALL_REDIRECT, P_ASSIGN,
										P_IONUMBER, P_PIPE, P_AND, P_END, P_SEMICOLON, 
										P_ANDIF, P_ORIF, P_ERROR};

	graph[P_WORD].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	// graph[P_SPSTRING].good_type = tab_good_type;
	// graph[P_DBQUOTE].good_type = tab_good_type;
}

void		init_redirect_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_WORD, P_ERROR};

	graph[P_GREAT].good_type = tab_good_type;
	graph[P_DGREAT].good_type = tab_good_type;
	graph[P_LESS].good_type = tab_good_type;
	graph[P_DLESS].good_type = tab_good_type;
	graph[P_GREATAND].good_type = tab_good_type;
	graph[P_LESSAND].good_type = tab_good_type;
	graph[P_DLESSDASH].good_type = tab_good_type;
}

void		init_assign_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_WORD, P_ERROR};

	graph[P_ASSIGN].good_type = tab_good_type;
}

void		init_process_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_WORD, ALL_REDIRECT, P_ASSIGN, P_NEWLINE, P_ERROR};
	static e_parser_state tab_type[] = {P_WORD, ALL_REDIRECT, P_ASSIGN, P_ERROR};

	graph[P_PIPE].good_type = tab_type;
	graph[P_AND].good_type = tab_good_type;
	graph[P_SEMICOLON].good_type = tab_good_type;
}

void		init_ionumber_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {ALL_REDIRECT, P_ERROR};

	graph[P_IONUMBER].good_type = tab_good_type;
}
