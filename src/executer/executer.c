/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:08:11 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/29 20:22:55 by sungjpar         ###   ########.fr       */
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
		waitpid(pid[index++], NULL, 0);
	}
}

static t_builtin_kind	get_builtin_kind(const char *str)
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

static t_bool	is_builtin_cmd(t_btree_node *ast)
{
	t_btree_node	*cmd;
	t_token			*token;

	cmd = get_left_leaf(ast);
	token = cmd->content;
	return (token->kind == TK_CMD && get_builtin_kind(token->str));
}

void	execute_builtin_cmd(t_btree_node *ast)
{
	t_btree_node	*cmd;
	t_token			*token;

	cmd = get_left_leaf(ast);
	token = cmd->content;
	if (get_builtin_kind(token->str) == BT_CD)
		builtin_cd(token->arguments, envp);
	else if (get_builtin_kind(token->str) == BT_PWD)
		builtin_pwd();
	else if (get_builtin_kind(token->str) == BT_EXPORT)
		builtin_export(token->arguments, envp);
	else if (get_builtin_kind(token->str) == BT_UNSET)
		builtin_unset(token->arguments, envp);
	else if (get_builtin_kind(token->str) == BT_ENV)
		builtin_env(envp);
	else if (get_builtin_kind(token->str) == BT_EXIT)
		builtin_exit(token->arguments);
	else
		return ;
}

/* main executer function*/
t_status	execute_commands_from_ast(t_btree_node *ast)
{
	const size_t	number_of_process = get_number_of_pipe(ast) + 1;
	pid_t			*pid;

	if (number_of_process == 1 && is_builtin_cmd(ast))
		execute_builtin_cmd(ast);
	else
	{
		pid = e_malloc(sizeof(pid_t) * number_of_process);
		explore_tree_and_execute_command(ast, pid, number_of_process);
		wait_childs(pid, number_of_process);
		free(pid);
	}
	return (SUCCESS);
}
