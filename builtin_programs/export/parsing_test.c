/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:35:44 by mingylee          #+#    #+#             */
/*   Updated: 2022/08/16 20:12:34 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*parsing_export(char *str)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(10000);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				result[j] = str[i];
				i++;
				j++;
			}
			result[j] = 0;
			printf("result = %s\n", result);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				result[j] = str[i];
				i++;
				j++;
			}
			result[j] = 0;
			printf("result = %s\n", result);
		}
		i++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	char	string[1024];

	string[0] = 'T';
	string[1] = 'E';
	string[2] = 'S';
	string[3] = 'T';
	string[4] = '=';
	string[5] = '"';
	string[6] = 't';
	string[7] = 'e';
	string[8] = '\'';
	string[9] = 's';
	string[10] = 't';
	string[11] = '"';
	string[12] = '"';
	string[13] = 'e';
	string[14] = ' ';
	string[15] = 's';
	string[16] = '"';
	string[17] = '\'';
	string[18] = '"';
	string[19] = ' ';
	string[20] = '"';
	string[21] = '\'';
	string[22] = '"';
	string[23] = 't';
	string[24] = '\'';
	string[25] = '\'';
	string[26] = '"';
	string[27] = '"';
	string[28] = 't';
	string[29] = 'e';
	string[30] = ' ';
	string[31] = 's';
	string[32] = 't';
	string[33] = '"';
	string[34] = 0;
	argv[1] = string;
	printf("%s\n", argv[1]);
	printf("my parsing : %s\n", parsing_export(argv[1]));
	return (0);
}
