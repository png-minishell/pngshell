/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:53:13 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 23:33:13 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

typedef struct s_btree_node
{
	struct s_btree_node	*parent;
	struct s_btree_node	*left_child;
	struct s_btree_node	*right_child;
	void				*content;
}	t_btree_node;

t_btree_node	*bst_get_root(t_btree_node *node);
t_btree_node	*bst_create_node(void *content);
t_btree_node	*bst_delete_node(t_btree_node *node);
void			bst_clear_tree(t_btree_node *root);
t_btree_node	*bst_link_left_child(t_btree_node *parent, t_btree_node *child);
t_btree_node	*bst_link_right_child(\
					t_btree_node *parent,
					t_btree_node *child);
t_btree_node	*bst_insert_node_left(\
					t_btree_node *target,
					t_btree_node *node);
t_btree_node	*bst_insert_node_right(\
					t_btree_node *target,
					t_btree_node *node);


#endif
