/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:15:22 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/30 20:16:20 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell_definitions.h"
#include "libft.h"

static void	get_last_argument(char *user_input)
{
	char	**splitted_string;
	size_t	index;

	splitted_string = ft_split(user_input, ' ');
	index = 0;
	while (splitted_string[index])
		++index;
	if (index)
		--index;
	change_envp_value("_", splitted_string[index], g_vars.envp);
	free_strings(splitted_string);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	change_under_bar(void)
{
	char	*exit_code;

	exit_code = ft_itoa(g_vars.exit_code);
	change_envp_value("?", exit_code, g_vars.envp);
	free(exit_code);
	return ;
}

static void	set_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	prompt(void)
{
	char			*user_cmd;
	t_btree_node	*ast;

	set_signal();
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
		change_under_bar();
		bst_clear_tree(ast, free_token);
		get_last_argument(user_cmd);
		free(user_cmd);
	}
}
