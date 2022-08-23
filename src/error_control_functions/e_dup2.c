/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_dup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:46:49 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 19:45:15 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"

t_status	e_dup2(const int fd1, const int fd2)
{
	if (dup2(fd1, fd2) == FAILED)
	{
		perror(NULL);
		exit(errno);
	}
	return (SUCCESS);
}
