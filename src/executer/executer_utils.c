/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:50:05 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "binary_tree.h"
#include "error_control_functions.h"
#include "executer.h"
#include "libft.h"

size_t	get_number_of_pipe(t_btree_node *const ast)
{
	t_btree_node	*node;
	size_t			num;

	num = 0;
	node = ast;
	while (node->left_child)
	{
		if (((t_token *)(node->content))->kind == TK_PIPE)
			++num;
		node = node->left_child;
	}
	return (num);
}

t_token_kind	get_node_token_kind(t_btree_node *node)
{
	return (((t_token *)(node->content))->kind);
}

t_status	do_token_purpose(t_btree_node *node)
{
	const t_token_kind	kind = get_node_token_kind(node);
	t_token				*r_token;

	r_token = NULL;
	if (node->right_child)
		r_token = node->right_child->content;
	if (kind == TK_LESS && r_token)
		do_infile_redirection(r_token->str);
	else if (kind == TK_GREATER && r_token)
		do_outfile_redirection(\
			r_token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (kind == TK_DOUBLE_LESS && r_token)
		do_heredoc_redirection(r_token->pipe_fd);
	else if (kind == TK_DOUBLE_GREATER && r_token)
		do_outfile_redirection(\
			r_token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (SUCCESS);
}
