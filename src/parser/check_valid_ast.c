/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:44:57 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/31 21:40:15 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell_definitions.h"

static t_bool	is_needed_child(t_token_kind kind)
{
	return (
		kind == TK_GREATER
		|| kind == TK_LESS
		|| kind == TK_PIPE
		|| kind == TK_DOUBLE_LESS
		|| kind == TK_DOUBLE_GREATER
	);
}

static t_bool	is_redirection(t_token_kind kind)
{
	return (
		kind == TK_GREATER
		|| kind == TK_LESS
		|| kind == TK_DOUBLE_LESS
		|| kind == TK_DOUBLE_GREATER
	);
}

static t_bool	is_word(t_token *token)
{
	return (
		token->kind == TK_WORD
		|| token->kind == TK_WORD_DOUBLE_QUOTE
	);
}

void	check_tree(t_btree_node *node, t_status *status)
{
	t_token	*token;

	if (node == NULL || *status == FAILED)
		return ;
	token = node->content;
	if ((token->kind == TK_ERROR)
		|| (is_needed_child(token->kind) && node->right_child == NULL))
	{
		*status = FAILED;
		return ;
	}
	if (is_redirection(token->kind)
		&& (node->right_child && !is_word(node->right_child->content)))
	{
		*status = FAILED;
		return ;
	}
	check_tree(node->left_child, status);
	check_tree(node->right_child, status);
}

t_status	check_valid_ast(t_btree_node *ast)
{
	t_status		status;

	if (ast == NULL)
		return (FAILED);
	status = SUCCESS;
	check_tree(ast, &status);
	return (status);
}
