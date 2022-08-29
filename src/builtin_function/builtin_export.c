/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:46:16 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 18:00:28 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_definitions.h"

static void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static void	sorting_envp(char **envp)
{
	int		envp_index;
	int		sorting_i;
	int		sorting_j;
	char	**temp_envp;

	temp_envp = envp;
	sorting_i = 0;
	while (envp[sorting_i])
	{
		sorting_j = sorting_i + 1;
		while (envp[sorting_j])
		{
			if (ft_strncmp(envp[sorting_i], envp[sorting_j]) > 0)
				ft_swap(&envp[sorting_i], &envp[sorting_j]);
			sorting_j++;
		}
		sorting_i++;
	}
	while (envp[envp_index])
	{
		printf("%s\n", envp[envp_index]);
		envp_index++;
	}
}

void	exporting_envp(char **arguments, char **envp)
{
	int		i;
	char	*key;

	i = 1;
	while (arguments[i])
	{
		key = get_key(arguments[i]);
		value = ft_strchar(arguments[i], '=') + 1;
		change_envp_value(key, value, envp);
		i++;
	}
}

// export 입력 시 정렬된 environment 출력
// 인자가 여러개 들어와도 다 바꿈

int	builtin_export(const char *str, char **arguments, char **envp)
{
	if (arguments[1] == NULL)
	{
		sorting_envp(envp);
		return (SUCCESS);
	}
	else
	{
		exporting_envp(arguments, envp);
		return (SUCCESS);
	}
	return (FAILED);
}
