/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:13:01 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/31 19:38:01 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "echo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx_byte;

	idx_byte = 0;
	while ((s1[idx_byte] || s2[idx_byte]) && idx_byte < n)
	{
		if (s1[idx_byte] != s2[idx_byte])
			return ((unsigned char) s1[idx_byte] - \
					(unsigned char) s2[idx_byte]);
		++idx_byte;
	}
	return (0);
}

t_option	get_option(int argc, char *argv[])
{
	size_t	idx;

	if (argc == 1)
		return (DEFAULT);
	else
	{
		idx = 1;
		if (ft_strncmp("-n", argv[1], 2) == 0)
		{
			idx = 1;
			while (argv[1][idx])
			{
				if (argv[1][idx] != 'n')
					return (DEFAULT);
				++idx;
			}
			return (N_MODE);
		}
		else
			return (DEFAULT);
	}
}
