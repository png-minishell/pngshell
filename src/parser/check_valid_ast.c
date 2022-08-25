/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:44:57 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:26:16 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell_definitions.h"

static t_bool	is_needed_child(t_token_kind kind)
{
	return (
		kind == TK_GREATER
		|| kind == TK_PIPE
		|| kind == TK_DOUBLE_LESS
		|| kind == TK_DOUBLE_GREATER
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
	check_tree(node->left_child, status);
	check_tree(node->right_child, status);
}

t_status	check_valid_ast(t_btree_node *ast)
{
	t_status		status;

	status = SUCCESS;
	check_tree(ast, &status);
	return (status);
}
