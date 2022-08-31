/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 20:20:09 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "executer.h"
#include "libft.h"

static void	wait_childs(pid_t *pid, size_t number_of_process)
{
	size_t	index;

	index = 0;
	while (index < number_of_process)
	{
		waitpid(pid[index++], &(g_vars.exit_code), 0);
		g_vars.exit_code >>= 8;
	}
}

static t_bool	is_builtin_cmd(t_btree_node *ast)
{
	t_btree_node	*cmd;
	t_token			*token;

	cmd = get_left_leaf(ast);
	token = cmd->content;
	return (token->kind == TK_CMD && get_builtin_kind(token->str));
}

/* main executer function*/
t_status	execute_commands_from_ast(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	pid_t			*pid;

	if (number_of_process == 1 && is_builtin_cmd(ast))
		execute_builtin_cmd(get_left_leaf(ast)->content);
	else
	{
		pid = e_malloc(sizeof(pid_t) * number_of_process);
		explore_tree_and_execute_command(ast, pid, number_of_process);
		signal(SIGINT, SIG_IGN);
		wait_childs(pid, number_of_process);
		signal(SIGINT, sigint_handler);
		free(pid);
	}
	return (SUCCESS);
}
