/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:38 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 21:51:11 by sungjpar         ###   ########.fr       */
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

static void	set_shell_level(void)
{
	char	*num;
	char	*itoa_n;

	num = get_value("SHLVL", g_vars.envp, g_vars.set);
	itoa_n = ft_itoa(ft_atoi(num) + 1);
	change_envp_value("SHLVL", itoa_n, g_vars.envp);
	free(num);
	free(itoa_n);
}

void	copy_envp(char **env)
{
	size_t	idx_env;
	size_t	idx_res;
	t_bool	shell_level_flag;

	idx_env = 0;
	idx_res = 0;
	shell_level_flag = FALSE;
	while (env[idx_env])
	{
		if (ft_strncmp("_=", env[idx_env], 2) == 0)
		{
			++idx_env;
			continue ;
		}
		else if (ft_strncmp("SHLVL=", env[idx_env], 6) == 0)
			shell_level_flag = TRUE;
		g_vars.envp[idx_res] = ft_strdup(env[idx_env]);
		++idx_env;
		++idx_res;
	}
	g_vars.envp[idx_res] = NULL;
	if (shell_level_flag)
		set_shell_level();
}

void	copy_set(char **env)
{
	size_t	idx_env;
	size_t	idx_res;

	idx_env = 0;
	idx_res = 0;
	if (env[idx_env] == NULL)
	{
		g_vars.set[0] = ft_strdup("SHLVL=1");
		g_vars.set[1] = ft_strdup(\
			"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		g_vars.set[2] = getcwd(NULL, 0);
		idx_res = 3;
	}
	g_vars.set[idx_res] = NULL;
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
	g_vars.cwd = getcwd(NULL, 0);
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
	free_strings(g_vars.envp);
	free_strings(g_vars.set);
	free(g_vars.cwd);
}
