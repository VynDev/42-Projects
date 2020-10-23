/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:32:40 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:32:41 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static char		*check(const char *big, const char *little, size_t little_len)
{
	if (ft_strnequ(big, little, little_len))
		return ((char *)big);
	return (NULL);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		little_len;
	char		*returned_value;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (*big && len > 0 && little_len <= len)
	{
		if (*big == *little)
		{
			returned_value = check(big, little, little_len);
			if (returned_value)
				return (returned_value);
		}
		len--;
		big++;
	}
	return (NULL);
}
