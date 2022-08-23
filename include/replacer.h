/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <sungjpar@student.42seoul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:59:16 by parksungj         #+#    #+#             */
/*   Updated: 2022/08/21 14:16:03 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACER_H
# define REPLACER_H

# include <stddef.h>

void	replace_backslash_and_copy_string(
			const char *str,
			char *res,
			size_t *idx_res);
char	replace_backslash(const char *str, size_t *index);
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
char	*replacer(const char *str);

#endif
