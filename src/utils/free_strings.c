/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:08:48 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/24 19:17:02 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"

void	free_strings(char **strings)
{
	size_t	index;

	index = 0;
	while (strings[index])
	{
		free(strings[index++]);
	}
	free(strings);
}
