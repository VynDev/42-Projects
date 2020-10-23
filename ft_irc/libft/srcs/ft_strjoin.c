/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:31:05 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 13:28:33 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int	check(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	return (1);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		s1_len;
	size_t		s2_len;
	char		*returned_char;

	if (!check(s1, s2))
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	returned_char = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!returned_char)
		return (NULL);
	while (i < s1_len)
	{
		returned_char[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		returned_char[i] = s2[i - s1_len];
		i++;
	}
	returned_char[i] = '\0';
	return (returned_char);
}
