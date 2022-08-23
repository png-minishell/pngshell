/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:36:44 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/21 14:13:41 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

char	*get_env_string(const char *str)
{
	size_t	idx_str;

	idx_str = 1;
	while (str[idx_str]
		&& !ft_isspace(str[idx_str])
		&& str[idx_str] != '$' && str[idx_str] != '\\')
	{
		++idx_str;
	}
	return (ft_substr(str, 0, idx_str - (str[idx_str] != 0)));
}

static void	replace_bakslash_and_copy_string(\
		const char *str,
		char *res,
		size_t *idx_res)
{
	size_t	idx_str;

	idx_str = 0;
	while (str[idx_str])
	{
		if (str[idx_str] == '\\')
			res[*idx_res] = replace_backslash(str + idx_str, &idx_str);
		else
			res[*idx_res] = str[idx_str];
		++idx_str;
		++(*idx_res);
	}
}

void	env_replacer(\
		const char *str, char *res, size_t *idx_str, size_t *idx_res)
{
	char	*env_str;
	char	*env_replaced_str;

	env_str = get_env_string(str);
	env_replaced_str = env_substituter(env_str, envp, set);
	replace_bakslash_and_copy_string(env_replaced_str, res, idx_res);
	*idx_str += ft_strlen(env_str);
	free(env_str);
	free(env_replaced_str);
}
