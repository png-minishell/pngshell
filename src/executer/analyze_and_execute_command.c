/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_and_execute_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:08:41 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:21:21 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "executer.h"
#include "libft.h"

static void	put_no_cmd_err(t_token *cmd_token)
{
	ft_putstr_fd("shell : ", 2);
	ft_putstr_fd(cmd_token->str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

t_status	analyze_and_execute_command(t_btree_node *const left_leaf)
{
	t_btree_node	*node;
	t_btree_node	*cmd_node;

	node = left_leaf;
	cmd_node = NULL;
	while (get_node_token_kind(node) != TK_PIPE)
	{
		do_token_purpose(node);
		if (get_node_token_kind(node) == TK_CMD)
			cmd_node = node;
		node = node->parent;
		if (node == NULL)
			break ;
	}
	if (cmd_node == NULL)
		return (SUCCESS);
	if (run_command(cmd_node->content) == FAILED)
		put_no_cmd_err(cmd_node->content);
	return (SUCCESS);
}
