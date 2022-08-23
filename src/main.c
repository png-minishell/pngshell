/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:38 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/23 18:00:21 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "executer.h"
#include <readline/readline.h>
#include "minishell_definitions.h"
#include "libft.h"

char **envp = NULL;
char **set = NULL;
int stdin_bak = 0;
int stdout_bak = 0;

int	main(int argc, char **argv, char **env)
{
	char			*user_cmd;
	t_btree_node	*ast;

	if (argc != 1)
	{
		printf("%s", argv[0]);
		return (0);
	}
	envp = env;
	set = env;
	while (1)
	{
		user_cmd = readline("\033[34m shell$ \033[0m");
		if (user_cmd[0] == 0)
		{
			free(user_cmd);
			continue ;
		}
		ast = create_ast_tree_from_string(user_cmd);
		if (check_valid_ast(ast) == SUCCESS)
		{
			run_heredoc(ast);
			execute_commands_from_ast(ast);
		}
		else
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
		}
		bst_clear_tree(ast, free_token);
		free(user_cmd);
	}
}
