/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:55:35 by guvillat          #+#    #+#             */
/*   Updated: 2019/10/02 15:55:54 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

b_node	*ast_add_node(b_node *root, b_node *left, b_node *right, e_ast_state nodetype, char *data)
{
	b_node *new;

	if (!root)
		return (root = NULL);
	new = ast_attach_node(root, left, right);
	new->type = nodetype;
	new->data = ft_strdup(data);
	new->data_len = ft_strlen(data);
	return (new);
}

b_node	*ast_attach_node(b_node *root, b_node *leftnode, b_node *rightnode)
{
	b_node *new;

	if (!root)
		return (NULL);
	if (!(new = (b_node*)malloc(sizeof(b_node))))
		return (NULL);
	new->left = leftnode;
	new->right = rightnode;
	new->type = B_NEW;
	new->data = NULL;
	new->data_len = 0;
	return (new);
}

void 	ast_delete(b_node *node)
{
	if (node->data)
		free(node->data);
	if (node->right)
		ast_delete(node->right);
	if (node->left)
		ast_delete(node->left);
}

void error_ast(t_lexer *lexer)
{
	ft_printf("ASTSTS   %u         %s\n", ((t_token*)lexer->tok->content)->id, ((t_token*)lexer->tok->content)->data);
}


// static void	bzero_ast(t_asting analyze)
// {
// 	int		index;

// 	index = 0;
// 	while (index < NB_AST_STATE)
// 	{
// 		analyze[index] = error_ast;
// 		++index;
// 	}
// }

b_ast *init_ast(void)
{
	b_ast *ast;

	ast = NULL;
	if (!(ast = (b_ast*)malloc(sizeof(b_ast))))
		return (ast);
	ast->state = B_START;
	// bzero_ast(ast->analyze);
	// ast->root = 
	return (ast);
}

b_ast *ast(t_lexer *lexer)
{
	b_ast *ast;

	if (!lexer || !lexer->tok)
		return (NULL);
	ast = init_ast();
	return (ast);
}
