/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:46:16 by mingylee          #+#    #+#             */
/*   Updated: 2022/09/01 21:57:40 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "minishell_definitions.h"
#include "libft.h"

void	exporting_envp(char **arguments, char **envp);
void	put_not_valid_identifier_err(char *err);

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
		put_not_valid_identifier_err(arguments[1]);
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
