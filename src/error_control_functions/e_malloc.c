/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:38:52 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 13:38:53 by sungjpar         ###   ########.fr       */
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
