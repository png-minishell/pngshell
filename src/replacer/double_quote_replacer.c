/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:39:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/21 00:10:39 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

char	*get_double_quote_string(const char *str)
{
	size_t	idx_str;

	idx_str = 1;
	while (str[idx_str] && str[idx_str] != '"')
	{
		if (ft_strncmp("\\\"", str + idx_str, 2) == 0)
			++idx_str;
		++idx_str;
	}
	return (ft_substr(str, 1, idx_str - (str[idx_str] != 0)));
}

void	double_quote_replacer(\
			const char *str, char *result, size_t *idx_str, size_t *idx_result)
{
	char	*double_quote_str;
	char	*env_replaced_str;
	size_t	idx_local_str;

	double_quote_str = get_double_quote_string(str);
	env_replaced_str = env_substituter(double_quote_str, envp, set);
	idx_local_str = 0;
	while (env_replaced_str[idx_local_str])
	{
		if (env_replaced_str[idx_local_str] == '\\')
		{
			result[*idx_result] = back_slash_replacer(\
					env_replaced_str + idx_local_str, &idx_local_str);
		}
		else
			result[*idx_result] = env_replaced_str[idx_local_str];
		++idx_local_str;
		++(*idx_result);
	}
	*idx_str += ft_strlen(double_quote_str) + 1;
	free(double_quote_str);
	free(env_replaced_str);
}
