/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_slash_replacer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:56 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/24 19:46:23 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replacer.h"

char	replace_backslash(const char *str, size_t *index)
{
	const char	next_char = *(str + 1);

	if (next_char == 0)
		return ('\\');
	if (next_char == 'a' && ++(*index))
		return ('\a');
	if (next_char == '\\' && ++(*index))
		return ('\\');
	if (next_char == 'b' && ++(*index))
		return ('\b');
	if (next_char == 't' && ++(*index))
		return ('\t');
	if (next_char == 'n' && ++(*index))
		return ('\n');
	if (next_char == 'v' && ++(*index))
		return ('\v');
	if (next_char == 'f' && ++(*index))
		return ('\f');
	if (next_char == 'r' && ++(*index))
		return ('\r');
	if (next_char == '\"' && ++(*index))
		return ('\"');
	if (next_char == '$' && ++(*index))
		return ('$');
	return ('\\');
}
