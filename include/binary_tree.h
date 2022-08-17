/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:53:13 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 14:53:20 by sungjpar         ###   ########.fr       */
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

t_btree_node	*create_node(void *content);
t_btree_node	*delete_node(t_btree_node *node);
void			clear_tree(t_btree_node *root);
t_btree_node	*link_left_child(t_btree_node *parent, t_btree_node *child);
t_btree_node	*link_right_child(t_btree_node *parent, t_btree_node *child);

#endif
