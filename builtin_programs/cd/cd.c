/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:27:32 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/17 15:52:11 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <readline/readline.h>

int	change_directory(char *input)
{
	DIR				*dir;
	struct dirent	*file;
	char			now_dir[1024];
	
	getcwd(now_dir, 1024);
	if ((dir = opendir(now_dir)) == 0)
		return (errno);
	if (!chdir(input))
		return (errno);
	return (0);
}

int	main(int argc, char **argv)
{
	char			*input;

	while (1)
	{
		input = readline(0);
		change_directory(input);
	}
	return (0);
}
