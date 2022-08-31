/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_skip_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:17:40 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/31 21:27:19 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "lexer.h"
#include "libft.h"

size_t	skip_space(const char *str, size_t start_index)
{
	size_t	result_index;

	result_index = start_index;
	while (ft_isspace(str[result_index]))
	{
		++result_index;
	}
	return (result_index);
}

size_t	skip_word(const char *str, size_t start_index)
{
	size_t	result_index;

	result_index = start_index;
	while (str[result_index]
		&& (!is_symbol(str[result_index]) || str[result_index] == '$')
		&& !ft_isspace(str[result_index]))
	{
		++result_index;
	}
	return (result_index);
}

size_t	skip_until_single_quote(const char *str, const size_t start_index)
{
	size_t	index;

	index = start_index;
	while (str[index] && str[index] != '\'')
		++index;
	return (index);
}

size_t	skip_until_double_quote(const char *str, const size_t start_index)
{
	size_t	index;

	index = start_index;
	while (str[index] && str[index] != '"')
	{
		if (ft_strncmp("\\\"", str + index, 2) == 0)
			++index;
		++index;
	}
	return (index);
}

size_t	get_word_end_index(\
		const char *str, const size_t start_index, const t_token_status status)
{
	if (status == ST_SINGLE_QUOTE)
		return (skip_until_single_quote(str, start_index));
	else if (status != ST_DOUBLE_QUOTE && status != ST_SINGLE_QUOTE)
		return (skip_word(str, start_index));
	else
		return (skip_until_double_quote(str, start_index));
}
