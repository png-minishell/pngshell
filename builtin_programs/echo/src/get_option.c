/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:13:01 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 15:35:02 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "echo.h"

static t_bool	strcmp(const char *s1, const char *s2)
{
	unsigned int	idx;

	idx = 0;
	while (s1[idx] && s2[idx] && (s1[idx] == s2[idx]))
	{
		++idx;
	}
	return (s1[idx] - s2[idx]);
}

t_option	get_option(int argc, char *argv[])
{
	if (argc == 1)
		return (DEFAULT);
	else
	{
		if (strcmp("-n", argv[1]) == 0)
			return (N_MODE);
		else
			return (DEFAULT);
	}
}
