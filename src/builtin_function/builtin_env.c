/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:10:35 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 18:12:07 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_definitions.h"

int	builtin_env(char **envp)
{
	int	envp_index;

	envp_index = 0;
	while (envp[envp_index])
	{
		printf("%s\n", envp[envp_index]);
		envp_index++;
	}
	return (SUCCESS);
}
