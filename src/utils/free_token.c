/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:36:26 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/22 21:49:40 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_definitions.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	free(token->str);
	if (token->arguments)
		free_strings(token->arguments);
	free(token);
}
