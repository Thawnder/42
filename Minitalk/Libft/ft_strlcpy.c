/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:42:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/04 11:18:13 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (len);
}
