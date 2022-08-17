/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_insert_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:04:14 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 17:11:38 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"

t_btree_node	*bst_insert_node(t_btree_node *target, t_btree_node *node)
{
	t_btree_node	*parent;

	if (target == NULL)
		return (NULL);
	if (target->parent == NULL)
		target->parent = node;
	else
	{
		parent = target->parent;
		if (parent->left_child == target)
			parent->left_child = node;
		else
			node->parent = parent;
		parent->right_child = node;
	}
	node->left_child = target;
	return (node);
}
