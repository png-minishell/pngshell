/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:39:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/23 18:40:54 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

static char	*get_double_quote_string(const char *str)
{
	size_t	idx_str;

	idx_str = 1;
	while (str[idx_str] && str[idx_str] != '"')
	{
		if (ft_strncmp("\\\"", str + idx_str, 2) == 0)
			++idx_str;
		++idx_str;
	}
	return (ft_substr(str, 0, idx_str + (str[idx_str] == '"')));
}

void	double_quote_replacer(\
			const char *str, char *res, size_t *idx_str, size_t *idx_res)
{
	char	*double_quote_str;
	char	*env_replaced_str;

	double_quote_str = get_double_quote_string(str);
	env_replaced_str = env_substituter(double_quote_str, envp, set);
	replace_backslash_and_copy_string(env_replaced_str, res, idx_res);
	*idx_str += ft_strlen(double_quote_str) + 1;
	free(double_quote_str);
	free(env_replaced_str);
}
