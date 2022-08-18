/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:41:03 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/18 15:23:36 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_control_functions.h"
#include "minishell_definitions.h"
#include "parser.h"

t_token	*create_malloced_token(t_token token)
{
	t_token	*new_token;

	new_token = e_malloc(sizeof(t_token));
	new_token->str = token.str;
	new_token->kind = token.kind;
	return (new_token);
}

t_token_type	get_token_type(t_token token)
{
	const t_token_kind	kind = token.kind;

	if (kind == TK_WORD || kind == TK_WORD_DOUBLE_QUOTE)
		return (TYPE_WORD);
	if (kind == TK_LESS || kind == TK_DOUBLE_LESS
		|| kind == TK_GREATER || kind == TK_DOUBLE_GREATER)
		return (TYPE_REDIRECT);
	if (kind == TK_CMD)
		return (TYPE_CMD);
	if (kind == TK_PIPE)
		return (TYPE_PIPE);
	return (TYPE_ERROR);
}

int	cmp_kind(t_token token1, t_token token2)
{
	const t_token_type	type1 = get_token_type(token1);
	const t_token_type	type2 = get_token_type(token2);

	return (type1 - type2);
}

t_btree_node	*find_node_position(\
		t_btree_node *current_node, t_btree_node *node)
{
	t_token	*current_node_token;
	t_token	*target_node_token;

	current_node_token = current_node->content;
	target_node_token = node->content;
	while (current_node->parent
		&& cmp_kind(*current_node_token, *target_node_token) < 0)
	{
		current_node = current_node->parent;
		current_node_token = current_node->content;
	}
	if (target_node_token->kind == TK_CMD)
	{
		while (current_node->left_child)
			current_node = current_node->left_child;
	}
	return (current_node);
}
