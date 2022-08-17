/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingylee <mingylee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:55:38 by mingylee          #+#    #+#             */
/*   Updated: 2022/03/30 14:30:32 by mingylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

static size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	if (!s)
		return (0);
	while (*str)
		str++;
	return (str - s);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	const size_t	src_len = ft_strlen(src);

	i = 0;
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	total_size = ft_strlen(s1) + ft_strlen(s2);
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	char			*result;

	if (!s1 || !s2)
		return (0);
	if (total_size <= 0)
	{
		result = (char *)malloc(sizeof(char));
		if (!(result))
			return (0);
		result[0] = '\0';
		return (result);
	}
	result = (char *)malloc(sizeof(char) * (total_size + 2));
	if (!(result))
		return (0);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	return (result);
}
