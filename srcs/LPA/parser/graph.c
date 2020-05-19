/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:47:16 by guvillat          #+#    #+#             */
/*   Updated: 2020/05/19 16:33:33 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_word_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {P_NEWLINE, P_WORD, P_GREAT, P_LESS
		, P_DGREAT, P_GREATAND, P_LESSAND, P_DLESS, P_DLESSDASH, P_ASSIGN
		, P_IONUMBER, P_PIPE, P_AND, P_END, P_SEMICOLON, P_ANDIF, P_ORIF
		, P_ANDDGREAT, P_ANDGREAT, P_ERROR};

	graph[P_WORD].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_ASSIGN].good_type = tab_good_type;
}

void	init_redirect_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {P_WORD, P_ERROR};
	static enum e_pstate heredoc[] = {P_WORD, P_LESS, P_ERROR};

	graph[P_GREAT].good_type = tab_good_type;
	graph[P_DGREAT].good_type = tab_good_type;
	graph[P_LESS].good_type = tab_good_type;
	graph[P_DLESS].good_type = heredoc;
	graph[P_GREATAND].good_type = tab_good_type;
	graph[P_LESSAND].good_type = tab_good_type;
	graph[P_DLESSDASH].good_type = heredoc;
	graph[P_ANDDGREAT].good_type = tab_good_type;
	graph[P_ANDGREAT].good_type = tab_good_type;
}

void	init_process_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {P_WORD, P_GREAT, P_LESS, P_DGREAT
		, P_GREATAND, P_LESSAND, P_DLESS, P_DLESSDASH, P_ASSIGN, P_NEWLINE
		, P_END, P_ANDDGREAT, P_ANDGREAT, P_ERROR};

	graph[P_AND].good_type = tab_good_type;
	graph[P_SEMICOLON].good_type = tab_good_type;
}

void	init_ionumber_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {P_GREAT, P_LESS, P_DGREAT
		, P_GREATAND, P_LESSAND, P_DLESS, P_DLESSDASH
		, P_ERROR};

	graph[P_IONUMBER].good_type = tab_good_type;
}

void	init_start_graph(t_graph *graph)
{
	static enum e_pstate	tab_good_type[] = {P_WORD, P_GREAT, P_LESS, P_DGREAT
		, P_GREATAND, P_LESSAND, P_DLESS, P_DLESSDASH, P_ASSIGN, P_IONUMBER
		, P_ANDDGREAT, P_ANDGREAT, P_START, P_END, P_ERROR};

	graph[P_START].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_PIPE].good_type = tab_good_type;
	graph[P_ORIF].good_type = tab_good_type;
	graph[P_ANDIF].good_type = tab_good_type;
}
