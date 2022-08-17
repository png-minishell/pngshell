/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_link_right_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:27:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 16:20:30 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"

t_btree_node	*bst_link_right_child(t_btree_node *parent, t_btree_node *child)
{
	if (parent == NULL)
		return (NULL);
	parent->right_child = child;
	child->parent = parent;
	return (parent);
}
