/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:51:36 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 15:52:52 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "error_control_functions.h"

t_status	e_pipe(int *fds)
{
	if (pipe(fds) == FAILED)
	{
		perror(NULL);
		exit(errno);
	}
	return (SUCCESS);
}
