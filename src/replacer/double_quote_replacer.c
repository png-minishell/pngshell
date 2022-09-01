/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:39:22 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/31 20:25:02 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

static char	*get_double_quote_string(const char *str)
{
	size_t	idx_str;
	t_bool	space_flag;

	idx_str = 1;
	space_flag = FALSE;
	while (str[idx_str] && str[idx_str] != '"')
	{
		if (ft_isspace(str[idx_str]))
			space_flag = TRUE;
		if (ft_strncmp("\\\"", str + idx_str, 2) == 0)
			++idx_str;
		++idx_str;
	}
	if (space_flag)
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

	double_quote_str = get_double_quote_string(str);
	env_replaced_str = \
		env_substituter(double_quote_str, g_vars.envp, g_vars.set);
	copy_string(env_replaced_str, res, idx_res);
	*idx_str += get_idx(str);
	free(double_quote_str);
	free(env_replaced_str);
}
