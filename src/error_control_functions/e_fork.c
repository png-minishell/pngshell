/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:21 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 20:00:54 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"

pid_t	e_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
	{
		perror(NULL);
		exit(errno);
	}
	return (pid);
}
