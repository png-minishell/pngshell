/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:38 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 17:56:02 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "executer.h"
#include "minishell_definitions.h"
#include "libft.h"

t_program_variables	g_vars;

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

void	copy_envp(char **env)
{
	size_t	idx_env;

	idx_env = 0;
	while (env[idx_env])
	{
		g_vars.envp[idx_env] = ft_strdup(env[idx_env]);
		++idx_env;
	}
	g_vars.envp[idx_env] = NULL;
}

void	copy_set(char **env)
{
	size_t	idx_env;

	idx_env = 0;
	while (env[idx_env])
	{
		g_vars.set[idx_env] = ft_strdup(env[idx_env]);
		++idx_env;
	}
	g_vars.set[idx_env] = NULL;
}

void	init_g_vars(char **env)
{
	g_vars.envp = ft_calloc(500, sizeof(char *));
	g_vars.set = ft_calloc(500, sizeof(char *));
	copy_envp(env);
	copy_set(env);
	g_vars.stdin_bak = dup(STDIN_FILENO);
	g_vars.stdout_bak = dup(STDOUT_FILENO);
	g_vars.exit_code = 0;
	g_vars.cwd = ft_strdup(getcwd(NULL, 0));
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
	{
		printf("%s", argv[0]);
		return (0);
	}
	init_g_vars(env);
	print_main_page();
	prompt();
}
