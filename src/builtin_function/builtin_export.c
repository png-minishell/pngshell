/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:46:16 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/31 21:57:09 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "minishell_definitions.h"
#include "libft.h"

static void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static void	sorting_envp(char **envp)
{
	int		idx_cur;
	int		idx_target;
	char	**temp_envp;

	temp_envp = envp;
	idx_cur = 0;
	while (envp[idx_cur])
	{
		idx_target = idx_cur + 1;
		while (envp[idx_target])
		{
			if (ft_strncmp(envp[idx_cur], envp[idx_target], -1) > 0)
				ft_swap(&envp[idx_cur], &envp[idx_target]);
			idx_target++;
		}
		idx_cur++;
	}
}

static void	print_envp(char **envp)
{
	int		idx_envp;

	idx_envp = 0;
	while (envp[idx_envp])
	{
		printf("%s\n", envp[idx_envp]);
		idx_envp++;
	}
}

void	exporting_envp(char **arguments, char **envp)
{
	int		idx_arg;
	char	*key;
	char	*value;

	idx_arg = 1;
	while (arguments[idx_arg])
	{
		if (ft_isdigit(arguments[idx_arg][0]))
		{
			ft_putstr_fd("shell: export: `", 2);
			ft_putstr_fd(arguments[idx_arg], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
			errno = 1;
			++idx_arg;
			continue ;
		}
		key = ft_substr(arguments[idx_arg], 0,
				ft_strchr(arguments[idx_arg], '=') - arguments[idx_arg]);
		value = ft_strdup(ft_strchr(arguments[idx_arg], '=') + 1);
		change_envp_value(key, value, envp);
		free(key);
		free(value);
		idx_arg++;
	}
}

int	builtin_export(char **arguments, char **envp)
{
	if (arguments[1] == NULL)
	{
		sorting_envp(envp);
		print_envp(envp);
		return (SUCCESS);
	}
	else if (ft_isdigit(arguments[1][0]))
	{
		ft_putstr_fd("shell: export: `", 2);
		ft_putstr_fd(arguments[1], 2);
		ft_putendl_fd("`: not a valid identifier", 2);
		errno = 1;
		return (1);
	}
	else if (ft_strchr(arguments[1], '=') == NULL)
		return (SUCCESS);
	else
	{
		exporting_envp(arguments, envp);
		return (SUCCESS);
	}
	return (FAILED);
}
