/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:54:59 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 17:30:24 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"
#include "minishell_definitions.h"
#include "error_control_functions.h"

static t_tokenized_string	*create_malloced_token(t_tokenized_string token)
{
	t_tokenized_string	*new_token;

	new_token = e_malloc(sizeof(t_tokenized_string));
	*new_token = token;
	return (new_token);
}

static t_btree_node	*find_node_position(\
		t_btree_node *current_node, t_btree_node *node)
{
	t_tokenized_string	*current_node_token;
	t_tokenized_string	*target_node_token;

	current_node_token = current_node->content;
	target_node_token = node->content;
	while (current_node->parent 
		&& current_node_token->kind < target_node_token->kind)
	{
		current_node = current_node->parent;
	}
	return (current_node);
}

/* CREATE AST FROM TOKENS*/
t_btree_node	*parser(t_tokenized_string *tokens)
{
	t_btree_node		*current_node;
	t_btree_node		*new_node;
	t_tokenized_string	*current_node_token;
	size_t				index;

	index = 0;
	current_node = NULL;
	while (tokens[index].kind != TK_ARR_END)
	{
		new_node = bst_create_node(create_malloced_token(tokens[index]));
		if (current_node == NULL)
			current_node = new_node;
		else
		{
			current_node_token = current_node->content;
			if (current_node_token->kind > tokens[index].kind)
			{
				current_node = bst_link_right_child(current_node, new_node);
			}
			else
			{
				current_node = find_node_position(current_node, new_node);
				current_node = bst_insert_node(current_node, new_node);
			}
		};
		++index;
	}
	return (bst_get_root(current_node));
}
