/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:27:32 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/16 20:44:10 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/*
void	passed_double_dot(argv[1])
{

}
*/

int	main(int argc, char **argv)
{
	DIR				*my_dir;
	struct dirent	*file;
	char			home[1024];

	my_dir = 0;
	if ((my_dir = opendir("/Users/mingylee/42seoul")) == 0)
	{
		printf("failed...\n");
		return (-1);
	}
	while ((file = readdir(my_dir)) != 0)
		printf("%s\n", file->d_name);
	closedir(my_dir);
	return (0);
}
