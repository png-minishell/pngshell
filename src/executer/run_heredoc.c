/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:14:22 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/23 14:26:23 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "executer.h"

void	run_heredoc(t_btree_node *root)
{
	t_token	*token;

	if (root == NULL)
		return ;
	if (get_node_token_kind(root) == TK_DOUBLE_LESS)
	{
		token = root->right_child->content;
		token->pipe_fd = heredoc(token->str);
	}
	run_heredoc(root->left_child);
	run_heredoc(root->right_child);
}
