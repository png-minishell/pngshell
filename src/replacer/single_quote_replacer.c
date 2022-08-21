/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_replacer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:05:33 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/20 23:26:43 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replacer.h"

void	single_quote_replacer(\
			const char *str, char *result, size_t *idx_str, size_t *idx_result)
{
	size_t	idx_local_str;

	idx_local_str = 1;
	while (str[idx_local_str] && str[idx_local_str] != '\'')
	{
		result[*idx_result] = str[idx_local_str];
		++idx_local_str;
		++(*idx_str);
		++(*idx_result);
	}
	*idx_str += (str[idx_local_str] == '\'');
}
