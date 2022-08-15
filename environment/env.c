/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:17:53 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/15 15:46:05 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	environment(char **envp)
{
	int	idx_envp;

	idx_envp = 0;
	while(envp[idx_envp])
	{
		printf("%s\n", envp[idx_envp]);
		idx_envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;

	readline();
}
