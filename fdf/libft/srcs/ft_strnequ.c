/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:32:25 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:34:50 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	while (*(unsigned char *)s1 == *(unsigned char *)s2 && n > 0)
	{
		if (!*s1)
			return (1);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (1);
	return (0);
}
