/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:12:28 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/29 19:02:30 by mingylee         ###   ########.fr       */
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
	int	str_index;

	str_index = 0;
	while (str[str_index])
	{
		if (!ft_isdigit(str[str_index]))
			return (FALSE);
		str_index++;
	}
	return (TRUE);
}

int	builtin_exit(const char *str, char **arguments, char **envp)
{
	int	arg_index;
	int	atoi_value;

	if (arguments[1] == NULL)
	{
		exit(1);
	}
	arg_index = 1;
	if (!is_digit_only(arguments[1])) // 숫자 외에 딴게 들어왔을경우
	{
		exit(255);
	}
	while (arguments[arg_index])
	{
		atoi_value = ft_atoi(arguments[arg_index]);
		arg_index++;
	}
	if (arg_index > 1)
		return (FAILED);
	exit((unsigned char)atoi_value);
}
