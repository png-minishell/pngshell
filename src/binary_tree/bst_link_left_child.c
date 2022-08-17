/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_link_left_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:26:35 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 15:26:53 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"

t_btree_node	*link_left_child(t_btree_node *parent, t_btree_node *child)
{
	if (parent == NULL)
		return (NULL);
	parent->left_child = child;
	return (parent);
}
