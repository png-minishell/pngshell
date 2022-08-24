/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:58:01 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/24 19:58:17 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_definitions.h"
#include "libft.h"

t_bool	is_symbol(const char c)
{
	return (ft_isinset(c, SYMBOLS));
}
