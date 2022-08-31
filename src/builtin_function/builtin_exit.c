/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:12:28 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/30 18:47:26 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "minishell_definitions.h"
#include "libft.h"

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

static void	put_err(char *err)
{
	ft_putstr_fd("shell: exit: ", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	builtin_exit(char **arguments)
{
	int	atoi_value;

	if (arguments[1] == NULL)
		atoi_value = 1;
	else if (!is_digit_only(arguments[1]))
	{
		put_err(arguments[1]);
		exit(255);
	}
	if (*(arguments + 1) != NULL)
	{
		ft_putendl_fd("shell: exit: too many arguments", 2);
		return (FAILED);
	}
	while (*arguments)
		atoi_value = ft_atoi(*arguments++);
	ft_putendl_fd("EXIT", 1);
	exit((unsigned char)atoi_value);
}
