/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:59:16 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/20 20:51:37 by parksungj        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACER_H
# define REPLACER_H

# include <stddef.h>

char	back_slash_replacer(const char *str, size_t *index);
void	single_quote_replacer(\
			const char *str,
			char *result, 
			size_t *idx_str, 
			size_t *idx_result);
void	double_quote_replacer(\
			const char *str,
			char *result, 
			size_t *idx_str,
			size_t *idx_result);
void	env_replacer(\
			const char *str,
			char *result,
			size_t *idx_str,
			size_t *idx_result);
size_t	get_replaced_string_size(const char *str);

#endif
