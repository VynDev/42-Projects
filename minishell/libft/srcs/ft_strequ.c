/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:30:35 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:30:37 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*(unsigned char *)s1 == *(unsigned char *)s2)
	{
		if (!*s1)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}
