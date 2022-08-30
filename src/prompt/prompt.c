/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:15:22 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/30 18:01:34 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "executer.h"
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell_definitions.h"
#include "libft.h"

t_program_variables	g_vars;

pid_t	pid;

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	prompt(void)
{
	char			*user_cmd;
	t_btree_node	*ast;

	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		user_cmd = readline("\033[34m shell$ \033[0m");
		if (user_cmd[0] == 0)
		{
			free(user_cmd);
			continue ;
		}
		ast = create_ast_tree_from_string(user_cmd);
		run_heredoc(ast);
		if (check_valid_ast(ast) == SUCCESS)
			execute_commands_from_ast(ast);
		else
			ft_putendl_fd("shell : syntax error", STDERR_FILENO);
		add_history(user_cmd);
		change_envp_value("?", ft_itoa(g_vars.exit_code), g_vars.envp);
		bst_clear_tree(ast, free_token);
		free(user_cmd);
	}
}
