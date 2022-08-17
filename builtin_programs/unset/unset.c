/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:55:36 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/17 16:33:22 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>

char	*ft_strjoin(char *s1, char *s2);

char	**unset(char *input, char **envp)
{
	int		i;
	char	*needle;

	i = 0;
	while (envp[i])
	{
		needle = ft_strjoin(input, "=");
		if(strnstr(envp[i], needle, strlen(needle)) != 0)
		{
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			break ;
		}
		free(needle);
		i++;
	}
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*input;

	while (1)
	{
		i = 0;
		input = readline(0);
		envp = unset(input, envp);
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	return (0);
}
