/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:44:24 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 19:45:04 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"

t_status	e_close(const int fd)
{
	if (close(fd) == FAILED)
	{
		perror(NULL);
		exit(errno);
	}
	return (SUCCESS);
}
