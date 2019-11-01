#include "sh42.h"

void		init_start_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_WORD, ALL_REDIRECT, P_ASSIGN, ALL_EXPANSION,
										P_IONUMBER, P_END, P_START, P_ERROR};
										//P_SEMICOLON,
	graph[P_START].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_ORIF].good_type = tab_good_type;
	graph[P_ANDIF].good_type = tab_good_type;
}

t_parser 	*ft_init_graph(t_parser *parser)
{
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_assign_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
	return (parser);
}

