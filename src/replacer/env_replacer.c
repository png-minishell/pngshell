/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:36:44 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/21 00:10:52 by parksungj        ###   ########.fr       */
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

void	env_replacer(\
		const char *str, char *result, size_t *idx_str, size_t *idx_result)
{
	char	*env_str;
	char	*env_replaced_str;
	size_t	idx_env_str;

	env_str = get_env_string(str);
	env_replaced_str = env_substituter(env_str, envp, set);
	idx_env_str = 0;
	while (env_replaced_str[idx_env_str])
	{
		if (env_replaced_str[idx_env_str] == '\\')
			result[*idx_result] = \
			back_slash_replacer(env_replaced_str + idx_env_str, &idx_env_str);
		else
			result[*idx_result] = env_replaced_str[idx_env_str];
		++idx_env_str;
		++(*idx_result);
	}
	*idx_str += ft_strlen(env_str);
	free(env_str);
	free(env_replaced_str);
}
