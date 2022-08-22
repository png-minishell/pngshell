/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */

/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:14:57 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 14:15:07 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replacer.h"

void	replace_backslash_and_copy_string(\
		const char *str,
		char *res,
		size_t *idx_res)
{
	size_t	idx_str;

	idx_str = 0;
	while (str[idx_str])
	{
		if (str[idx_str] == '\\')
			res[*idx_res] = replace_backslash(str + idx_str, &idx_str);
		else
			res[*idx_res] = str[idx_str];
		++idx_str;
		++(*idx_res);
	}
}
