/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 19:38:47 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "binary_tree.h"
#include "error_control_functions.h"
#include "executer.h"
#include "libft.h"

static size_t	get_argv_size(t_btree_node *node)
{
	size_t	num;

	num = 0;
	while (node->right_child)
	{
		node = node->right_child;
		++num;
	}
	return (num);
}

static t_cmd	get_cmd(t_btree_node *const cmd_node)
{
	const size_t	argv_size = get_argv_size(cmd_node);
	t_cmd			cmd;
	char			**argv;
	size_t			index;
	t_btree_node	*node;

	argv = e_malloc(sizeof(char *) * (argv_size + 1));
	index = 0;
	node = cmd_node->right_child;
	while (node)
	{
		argv[index] = ft_strdup(((t_token *)(node->content))->str);
		node = node->right_child;
		++index;
	}
	argv[index] = NULL;
	cmd.cmd_string = ((t_token *)(cmd_node->content))->str;
	cmd.arguments = argv;
	return (cmd);
}

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

t_status	do_token_purpose(t_btree_node *node, t_cmd *cmd)
{
	const t_token		*token = node->content;
	const t_token_kind	kind = get_node_token_kind(node);

	if (kind == TK_CMD)
		*cmd = get_cmd(node);
	else if (kind == TK_LESS)
		do_infile_redirection(token->str);
	else if (kind == TK_GREATER)
		do_outfile_redirection(token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (kind == TK_DOUBLE_LESS)
		do_heredoc_redirection(node);
	else if (kind == TK_DOUBLE_GREATER)
		do_outfile_redirection(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (FAILED);
}
