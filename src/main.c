/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:38 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 21:07:00 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "executer.h"
#include <readline/readline.h>
#include "minishell_definitions.h"

char **envp = NULL;
char **set = NULL;
int stdin_bak = 0;
int stdout_bak = 0;

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
	{
		printf("%s", argv[0]);
		return (0);
	}
	envp = env;
	set = env;
	while(1)
	{
		char	*user_cmd;
		user_cmd = readline("shell$ ");
		t_btree_node *ast = parser(user_cmd);
		run_heredoc(ast);
		executer(ast);
	}
}
