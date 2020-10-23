/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:33:05 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:39:41 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static char		*check(const char *haystack,
		const char *needle, size_t needle_len)
{
	if (ft_strnequ(haystack, needle, needle_len))
		return ((char *)haystack);
	return (NULL);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t		needle_len;
	char		*returned_value;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			returned_value = check(haystack, needle, needle_len);
			if (returned_value)
				return (returned_value);
		}
		haystack++;
	}
	return (NULL);
}
