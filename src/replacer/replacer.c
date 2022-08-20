/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:\
 *   parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:31:46 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/20 23:28:54 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell_definitions.h"
#include "error_control_functions.h"
#include "replacer.h"
#include "libft.h"

static void	scan_and_replace(\
		const char *str, char *result_tmp, size_t *idx_str, size_t *idx_result)
{
	if (str[*idx_str] == '\\')
		result_tmp[(*idx_result)++] \
			= back_slash_replacer(str + *idx_str, idx_str);
	else if (str[*idx_str] == '\'')
		single_quote_replacer(str + *idx_str, result_tmp, idx_str, idx_result);
	else if (str[*idx_str] == '"')
		double_quote_replacer(str + *idx_str, result_tmp, idx_str, idx_result);
	else if (str[*idx_str] == '$' && str[*idx_str + 1])
		env_replacer(str + *idx_str, result_tmp, idx_str, idx_result);
	else
		result_tmp[(*idx_result)++] = str[*idx_str];
}

char	*replacer(const char *str)
{
	size_t	idx_str;
	size_t	idx_result;
	char	*result_tmp;
	char	*result;

	idx_str = 0;
	idx_result = 0;
	result_tmp = e_malloc(sizeof(char) * (get_replaced_string_size(str)));
	while (str[idx_str])
	{
		scan_and_replace(str, result_tmp, &idx_str, &idx_result);
		if (str[idx_str] == 0)
			break ;
		++idx_str;
	}
	result_tmp[idx_result] = 0;
	result = ft_strdup(result_tmp);
	free(result_tmp);
	return (result);
}

char	**envp;
char	**set;

int	main(void)
{
	char	*tc = "\\$PATH hello i\\\'m \"$HOME \\$\" \"\\\"\" path is \"$PATH adb\\$PATH\"\n\r 'say' '$PATH' $PATH";
	char	**etmp = e_malloc(sizeof(char *) * 2);
	char	**stmp = e_malloc(sizeof(char *) * 2);
	etmp[0] = "HOME=i'm_replaced";
	etmp[1] = NULL;
	stmp[0] = "PATH=I'M_REPLACED";
	stmp[1] = NULL;
	envp = etmp;
	set = stmp;
	printf("%s\n", tc);
	printf("%s", replacer(tc));
	//system("leaks a.out > test.txt; cat test.txt; rm test.txt");
}
