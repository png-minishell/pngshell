/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:18:16 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/31 19:46:11 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "echo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

static int	pass_options(char **strings, t_option mode)
{
	size_t	idx_str;
	size_t	idx_chr;

	if (mode == DEFAULT)
		return (1);
	idx_str = 2;
	while (ft_strncmp("-n", strings[idx_str], 2) == 0)
	{
		idx_chr = 1;
		while (strings[idx_str][idx_chr])
		{
			if (strings[idx_str][idx_chr] != 'n')
				return (idx_str);
			++idx_chr;
		}
		++idx_str;
	}
	return (idx_str);
}

t_status	echo_string(char **strings, t_option mode)
{
	size_t	idx_str;

	idx_str = pass_options(strings, mode);
	while (strings[idx_str])
	{
		printf("%s", strings[idx_str]);
		++idx_str;
		if (strings[idx_str])
			printf(" ");
	}
	if (mode == DEFAULT)
		printf("\n");
	return (SUCCESS);
}
