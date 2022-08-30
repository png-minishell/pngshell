/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:00:59 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 20:21:27 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"

void	unset_envp(char *argument, char **envp)
{
	int		idx_envp;
	char	*key;

	key = get_key(argument);
	idx_envp = get_envp_index(key, envp);
	free(key);
	if (idx_envp == -1)
		return ;
	while (envp[idx_envp])
	{
		envp[idx_envp] = envp[idx_envp + 1];
		idx_envp++;
	}
}

int	builtin_unset(char **arguments, char **envp)
{
	int	idx_arg;

	idx_arg = 1;
	if (arguments[1] == 0)
		return (FAILED);
	while (arguments[idx_arg])
	{
		unset_envp(arguments[idx_arg], envp);
		idx_arg++;
	}
	return (SUCCESS);
}
