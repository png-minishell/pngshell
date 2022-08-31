/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:16:22 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/31 20:20:19 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "libft.h"

t_bool	has_space(const char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (TRUE);
		++str;
	}
	return (FALSE);
}
