/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:31:38 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/25 18:43:11 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i;

	len_dst = 0;
	while (dst[len_dst] && len_dst < size)
		len_dst++;
	i = 0;
	if (len_dst < size)
	{
		while ((i + len_dst) < (size - 1) && src[i])
		{
			dst[i + len_dst] = src[i];
			i++;
		}
		dst[i + len_dst] = '\0';
	}
	return (len_dst + ft_strlen(src));
}
