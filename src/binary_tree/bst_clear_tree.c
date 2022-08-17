/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_clear_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:26:04 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 15:27:48 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "binary_tree.h"

void	bst_clear_tree(t_btree_node *root)
{
	if (root == NULL)
		return ;
	clear_tree(root->left_child);
	clear_tree(root->right_child);
	delete_node(root);
}
