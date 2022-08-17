/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:25:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 15:25:52 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
