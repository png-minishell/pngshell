/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:19:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 20:54:06 by sungjpar         ###   ########.fr       */
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

t_builtin_kind	get_builtin_kind(const char *str)
{
	if (ft_strncmp(str, "cd", -1) == 0)
		return (BT_CD);
	else if (ft_strncmp(str, "env", -1) == 0)
		return (BT_ENV);
	else if (ft_strncmp(str, "exit", -1) == 0)
		return (BT_EXIT);
	else if (ft_strncmp(str, "export", -1) == 0)
		return (BT_EXPORT);
	else if (ft_strncmp(str, "pwd", -1) == 0)
		return (BT_PWD);
	else if (ft_strncmp(str, "unset", -1) == 0)
		return (BT_UNSET);
	else
		return (BT_NONE);
}

void	execute_builtin_cmd(t_token *token)
{
	if (get_builtin_kind(token->str) == BT_CD)
		builtin_cd(token->arguments, g_vars.envp);
	else if (get_builtin_kind(token->str) == BT_PWD)
		builtin_pwd();
	else if (get_builtin_kind(token->str) == BT_EXPORT)
		builtin_export(token->arguments, g_vars.envp);
	else if (get_builtin_kind(token->str) == BT_UNSET)
		builtin_unset(token->arguments, g_vars.envp);
	else if (get_builtin_kind(token->str) == BT_ENV)
		builtin_env(g_vars.envp);
	else if (get_builtin_kind(token->str) == BT_EXIT)
		builtin_exit(token->arguments);
	else
		return ;
}
