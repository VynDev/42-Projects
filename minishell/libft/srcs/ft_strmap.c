/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:31:35 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 12:54:31 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*returned_char;

	if (!s || !f)
		return (NULL);
	i = 0;
	returned_char = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!returned_char)
		return (NULL);
	while (s[i])
	{
		returned_char[i] = (*f)(s[i]);
		i++;
	}
	returned_char[i] = '\0';
	return (returned_char);
}
