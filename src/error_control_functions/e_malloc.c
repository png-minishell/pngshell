/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:38:52 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/17 14:51:22 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "error_control_functions.h"

void	*e_malloc(size_t malloc_size)
{
	void	*ptr;

	ptr = malloc(malloc_size);
	if (ptr == NULL)
	{
		perror(NULL);
		exit(errno);
	}
	return (ptr);
}
