/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_skip_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:17:40 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/17 20:45:06 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static t_bool	is_symbol(const char c)
{
	return (ft_isinset(c, SYMBOLS));
}

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
		&& !is_symbol(str[result_index]) && !ft_isspace(str[result_index]))
	{
		++result_index;
	}
	return (result_index);
}

size_t	skip_until_quote(\
	const char *str, const size_t start_index, const t_token_status status)
{
	char	quote;
	size_t	index;

	if (status == ST_DOUBLE_QUOTE)
		quote = '\"';
	else if (status == ST_SINGLE_QUOTE)
		quote = '\'';
	index = start_index;
	while (str[index] && str[index] != quote)
	{
		++index;
	}
	return (index);
}

size_t	get_word_end_index(\
		const char *str, const size_t start_index, const t_token_status status)
{
	if (status != ST_DOUBLE_QUOTE && status != ST_SINGLE_QUOTE)
		return (skip_word(str, start_index));
	else
		return (skip_until_quote(str, start_index, status));
}
