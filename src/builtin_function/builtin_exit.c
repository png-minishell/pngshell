/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:12:28 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 19:32:24 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "minishell_definitions.h"
#include "libft.h"

// exit 는 개같은 함수다.
// 이유는
// exit 1 2 3 4 는too many arguments가 뜨고 종료 되지 않지만
// exit 1a 2 3 4 는 numeric arguments required로 종료 된다
// 따라서 첫번째 인자의 numeric만 체크하고 이후에 다른걸 체크한다.

static int	is_digit_only(char *str)
{
	int	idx_str;

	idx_str = 0;
	while (str[idx_str])
	{
		if (!ft_isdigit(str[idx_str]))
			return (FALSE);
		idx_str++;
	}
	return (TRUE);
}

int	builtin_exit(const char *str, char **arguments, char **envp)
{
	int	idx_arg;
	int	atoi_value;

	if (arguments[1] == NULL)
		exit(1);
	if (!is_digit_only(arguments[1]))
	{
		ft_putstr_fd("shell: exit: ", 2);
		ft_putstr_fd(arguments[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	idx_arg = 1;
	while (arguments[idx_arg])
	{
		atoi_value = ft_atoi(arguments[idx_arg]);
		idx_arg++;
	}
	if (idx_arg > 1)
	{
		ft_putendl_fd("shell: exit: too many arguments", 2);
		return (FAILED);
	}
	exit((unsigned char)atoi_value);
}
