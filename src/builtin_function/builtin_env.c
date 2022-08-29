/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:10:35 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 19:27:58 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_definitions.h"

int	builtin_env(char **envp)
{
	int	idx_envp;

	idx_envp = 0;
	while (envp[idx_envp])
	{
		printf("%s\n", envp[idx_envp]);
		idx_envp++;
	}
	return (SUCCESS);
}
