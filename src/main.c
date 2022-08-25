/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:38 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/25 17:22:06 by sungjpar         ###   ########.fr       */
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

static void	print_main_page(void)
{
	printf("%s", "\033[36m");
	printf(\
	"\n\
	____  _   ________   _____ __  __________    __ \n\
	/ __ \\/ | / / ____/  / ___// / / / ____/ /   / / \n\
	/ /_/ /  |/ / / __    \\__ \\/ /_/ / __/ / /   / /  \n\
	/ ____/ /|  / /_/ /   ___/ / __  / /___/ /___/ /___\n\
	/_/   /_/ |_/\\____/   /____/_/ /_/_____/_____/_____/\n\
	\n");
	printf("\
		\
		%sby %sP%sark sungjun a%sN%sd lee min%sG%syu\n",
		"\033[33m", "\033[36m",
		"\033[33m", "\033[36m",
		"\033[33m", "\033[36m",
		"\033[33m");
	printf("\n\n%s", "\033[0m");
}

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
	print_main_page();
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
			ft_putendl_fd("shell : syntax error", STDERR_FILENO);
		}
		bst_clear_tree(ast, free_token);
		free(user_cmd);
	}
}
