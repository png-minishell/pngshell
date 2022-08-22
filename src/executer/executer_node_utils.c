/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_node_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:20:40 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 15:19:34 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executer.h"
#include "libft.h"

t_btree_node	*get_left_leaf(t_btree_node *const root)
{
	t_btree_node	*node;

	node = root;
	while (node->left_child)
	{
		node = node->left_child;
	}
	return (node);
}

t_btree_node	*get_next_root(t_btree_node *const left_leaf)
{
	t_btree_node	*node;

	node = left_leaf;
	if (get_node_token_kind(node) == TK_PIPE)
	{
		if (node->parent)
			return (node->parent);
		else
			return (node);
	}
	else
	{
		while (node->parent && get_node_token_kind(node) != TK_PIPE)
		{
			node = node->parent;
		}
	}
	return (node);
}
