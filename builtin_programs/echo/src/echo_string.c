/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:18:16 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 15:34:12 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "echo.h"

t_status	echo_string(char **strings, t_option mode)
{
	unsigned int	strings_index;

	strings_index = (unsigned int)mode + 1;
	while (strings[strings_index])
	{
		printf("%s", strings[strings_index]);
		++strings_index;
		if (strings[strings_index])
			printf(" ");
	}
	if (mode == DEFAULT)
		printf("\n");
	return (SUCCESS);
}
