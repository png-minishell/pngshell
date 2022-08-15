/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:00 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 14:47:51 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "binary_tree.h"
#include "error_control_functions.h"

t_btree_node	*create_node(void *content)
{
	t_btree_node	*new_node;
	
	new_node = e_malloc(sizeof(t_btree_node));
	new_node->parent = NULL;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	new_node->content = content;
	return (new_node);
}

t_btree_node	*delete_node(t_btree_node *node)
{
	free(node->content);
	free(node);
	return (NULL);
}

t_btree_node	*link_left_child(t_btree_node *parent, t_btree_node *child)
{
	if (parent == NULL)
		return (NULL);
	parent->left_child = child;
	return (parent);
}

t_btree_node	*link_right_child(t_btree_node *parent, t_btree_node *child)
{
	if (parent == NULL)
		return (NULL);
	parent->right_child = child;
	return (parent);
}
