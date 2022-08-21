/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:54:59 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 18:00:25 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "binary_tree.h"
#include "parser.h"
#include "lexer.h"

static void	insert_node(t_btree_node *current_node, t_btree_node *new_node)
{
	t_token	*current_node_token;
	t_token	*new_node_token;

	current_node_token = (t_token *)(current_node->content);
	new_node_token = (t_token *)(new_node->content);
	if (new_node_token->kind == TK_CMD)
		bst_link_left_child(current_node, new_node);
	else if (cmp_kind(*current_node_token, *new_node_token) > 0)
	{
		bst_link_left_child(new_node, current_node->right_child);
		bst_link_right_child(current_node, new_node);
	}
	else
		bst_insert_node_left(current_node, new_node);

}

t_btree_node	*create_token_ast_from_tokens(t_token *tokens)
{
	t_btree_node	*current_node;
	t_btree_node	*new_node;
	t_token			*current_node_token;
	size_t			index;

	index = 0;
	current_node = NULL;
	while (tokens[index].kind != TK_ARR_END)
	{
		new_node = bst_create_node(create_malloced_token(tokens[index]));
		if (current_node != NULL)
		{
			current_node_token = (t_token *)current_node->content;
			if (cmp_kind(*current_node_token, tokens[index]) >= 0)
				bst_link_right_child(current_node, new_node);
			else
			{
				current_node = find_node_position(current_node, new_node);
				insert_node(current_node, new_node);
			}
		}
		current_node = new_node;
		++index;
	}
	return (bst_get_root(current_node));
}

t_btree_node	*parser(const char *str)
{
	t_token			*tokens;
	t_btree_node	*ast_root;
	char			*replaced_str;

	replaced_str = replacer(str);
	tokens = lexer(replaced_str);
	ast_root = create_token_ast_from_tokens(tokens);
	free(tokens);
	free(replaced_str);
	return (ast_root);
}

