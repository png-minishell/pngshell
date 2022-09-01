/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:00:59 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/31 21:50:39 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "libft.h"

void	unset_envp(char *argument, char **envp)
{
	int		idx_envp;
	char	*key;

	key = ft_substr(argument, 0, ft_strchr(argument, '=') - argument);
	idx_envp = get_envp_index(key, envp);
	free(key);
	if (envp[idx_envp] == NULL)
		return ;
	free(envp[idx_envp]);
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
		return (SUCCESS);
	while (arguments[idx_arg])
	{
		unset_envp(arguments[idx_arg], envp);
		unset_envp(arguments[idx_arg], g_vars.set);
		idx_arg++;
	}
	return (SUCCESS);
}
