/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_replaced_string_size.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:51:47 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/22 20:31:53 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"
#include "replacer.h"
#include "libft.h"

size_t	get_replaced_string_size(const char *str)
{
	char	*env_replaced_str;
	size_t	size;

	env_replaced_str = env_substituter(str, envp, set);
	size = ft_strlen(env_replaced_str) + ft_strlen(str);
	free(env_replaced_str);
	return (size);
}
