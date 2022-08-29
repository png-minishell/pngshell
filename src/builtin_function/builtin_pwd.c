/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:41:45 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 17:43:08 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_definitions.h"

int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		return (SUCCESS);
	}
	return (FAILED);
}
