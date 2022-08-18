/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_get_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:27:21 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 17:28:12 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"

t_btree_node	*bst_get_root(t_btree_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->parent)
	{
		node = node->parent;
	}
	return (node);
}
