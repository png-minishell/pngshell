/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_delete_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:25:31 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 19:49:47 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "binary_tree.h"

t_btree_node	*bst_delete_node(t_btree_node *node, void (*free_func)(void *))
{
	free_func(node->content);
	free(node);
	return (NULL);
}
