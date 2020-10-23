/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:33:11 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 12:22:24 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*returned_char;

	if (!s)
		return (NULL);
	i = 0;
	returned_char = (char *)malloc(sizeof(char) * (len + 1));
	if (!returned_char)
		return (NULL);
	while (len > 0)
	{
		returned_char[i] = s[start];
		i++;
		start++;
		len--;
	}
	returned_char[i] = '\0';
	return (returned_char);
}
