/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:39:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/09/01 18:56:34 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

static char	*get_double_quote_string(const char *str)
{
	size_t	idx_str;
	t_bool	quote_flag;

	idx_str = 1;
	quote_flag = FALSE;
	while (str[idx_str] && (str[idx_str] != '"'
			|| (idx_str && str[idx_str - 1] == '\\' && str[idx_str] == '"')))
	{
		if (ft_isspace(str[idx_str]) || is_symbol(str[idx_str]))
			quote_flag = TRUE;
		if (ft_strncmp("\\\"", str + idx_str, 2) == 0)
			++idx_str;
		++idx_str;
	}
	if (quote_flag)
		return (ft_substr(str, 0, idx_str + (str[idx_str] == '"')));
	else
		return (ft_substr(str, 1, idx_str - (str[idx_str] == '"')));
}

static size_t	get_idx(const char *str)
{
	size_t	idx_str;

	idx_str = 1;
	while (str[idx_str] && str[idx_str] != '"')
	{
		if (ft_strncmp("\\\"", str + idx_str, 2) == 0)
			++idx_str;
		++idx_str;
	}
	return (idx_str);
}

void	double_quote_replacer(\
			const char *str, char *res, size_t *idx_str, size_t *idx_res)
{
	char	*double_quote_str;
	char	*env_replaced_str;

	env_replaced_str = \
		env_substituter(str, g_vars.envp, g_vars.set);
	double_quote_str = get_double_quote_string(env_replaced_str);
	copy_string(double_quote_str, res, idx_res);
	*idx_str += get_idx(str);
	free(double_quote_str);
	free(env_replaced_str);
}
