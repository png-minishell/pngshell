/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:36:36 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/17 17:12:27 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = readline(0);
	exit((unsigned char)atoi(input));
}
