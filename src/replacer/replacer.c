/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:53 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 14:26:27 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "replacer.h"
#include "libft.h"

static void	scan_and_replace(\
		const char *str, char *res)
{
	size_t	idx_str;
	size_t	idx_res;

	idx_str = 0;
	idx_res = 0;
	while (str[idx_str])
	{
		if (str[idx_str] == '\\')
			res[(idx_res)++] = replace_backslash(str + idx_str, &idx_str);
		else if (str[idx_str] == '\'')
			single_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '"')
			double_quote_replacer(str + idx_str, res, &idx_str, &idx_res);
		else if (str[idx_str] == '$' && str[idx_str + 1])
			env_replacer(str + idx_str, res, &idx_str, &idx_res);
		else
			res[idx_res++] = str[idx_str];
		if (str[idx_str] == 0)
			break ;
		++idx_str;
	}
	res[idx_res] = 0;
}

char	*replacer(const char *str)
{
	char	*result_tmp;
	char	*result;

	result_tmp = e_malloc(sizeof(char) * (get_replaced_string_size(str)));
	scan_and_replace(str, result_tmp);
	result = ft_strdup(result_tmp);
	free(result_tmp);
	return (result);
}

/* test code */
#include <stdio.h>
char	**envp;
char	**set;

int	main(void)
{
	char	*tc2 = "cat -e < hello.txt | grep \"hello\" | echo $PATH | cat -e '$HOME' > $PATH";
	char	*tc = "\\$PATH hello i\\\'m \"$HOME \\$\" \"\\\"\" path is \"$PATH adb\\$PATH\"\n\r 'say' '$PATH' $PATH";
	char	**etmp = e_malloc(sizeof(char *) * 2);
	char	**stmp = e_malloc(sizeof(char *) * 2);
	etmp[0] = "HOME=i'm_replaced";
	etmp[1] = NULL;
	stmp[0] = "PATH=I'M_REPLACED";
	stmp[1] = NULL;
	envp = etmp;
	set = stmp;
	printf("%s\n", tc2);
	char	*res = replacer(tc2);
	printf("%s\n", res);
	free(res);
	system("leaks a.out > test.txt; cat test.txt; rm test.txt");
}
