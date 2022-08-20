/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_slash_replacer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:56 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/20 23:26:51 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replacer.h"

char	back_slash_replacer(const char *str, size_t *index)
{
	const char	next_char = *(str + 1);

	if (next_char == 0)
		return ('\\');
	if (next_char == 'a' && ++(*index))
		return (7);
	if (next_char == 'b' && ++(*index))
		return (8);
	if (next_char == 't' && ++(*index))
		return (9);
	if (next_char == 'n' && ++(*index))
		return (10);
	if (next_char == 'v' && ++(*index))
		return (11);
	if (next_char == 'f' && ++(*index))
		return (12);
	if (next_char == 'r' && ++(*index))
		return (13);
	if (next_char == '"' && ++(*index))
		return ('"');
	if (next_char == '\'' && ++(*index))
		return ('\'');
	if (next_char == '$' && ++(*index))
		return ('$');
	return ('\\');
}
