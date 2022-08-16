/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:17:53 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/16 15:27:37 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	environment(char **envp)
{
	int		envp_index;

	envp_index = 0;
	while (envp[envp_index])
	{
		printf("%s\n",envp[envp_index]);
		envp_index++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	(void)argv;
	environment(envp);
	return (0);
}
