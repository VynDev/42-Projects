/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:31:15 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:31:17 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		i;
	size_t		j;
	size_t		dest_length;

	i = 0;
	j = 0;
	dest_length = ft_strlen(dest);
	while (dest[i])
		i++;
	while (src[j] && i + j < n - 1 && n > 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	if (n < i + j)
		return (n + ft_strlen(src));
	return (dest_length + ft_strlen(src));
}
