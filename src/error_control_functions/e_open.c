/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_open.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:42:00 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 19:45:38 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"

int	e_open(const char *path, int flag, int mode)
{
	int	fd;

	fd = open(path, flag, mode);
	if (fd == FAILED)
	{
		perror(NULL);
		exit(errno);
	}
	return (fd);
}
