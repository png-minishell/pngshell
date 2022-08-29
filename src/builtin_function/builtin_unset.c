/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:00:59 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 18:10:11 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"

void	unset_envp(char *arguments, char **envp)
{
	int	envp_index;

	envp_index = get_envp_index(get_key(arguments), envp);
	if (envp_index == -1)
		return ;
	while (envp[envp_index])
	{
		envp[envp_index] = envp[envp_index + 1];
		envp_index++;
	}
}

int	builtin_unset(const char *str, char **arguments, char **envp)
{
	int	arg_index;

	arg_index = 1;
	// unset 만 입력 했을 때 무슨 동작 하는지 모르겠음... 아마 아무 동작 안하는거 같음
	if (arguments[1] == 0)
		return (FAILED);
	while (arguments[arg_index])
	{
		unset_envp(arguments[arg_index], envp);
		arg_index++;
	}
	return (SUCCESS);
}
