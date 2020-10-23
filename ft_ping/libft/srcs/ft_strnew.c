/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:32:34 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:32:36 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	size_t		i;
	char		*allocated_memory;

	i = 0;
	allocated_memory = (char *)malloc(sizeof(char) * (size + 1));
	if (!allocated_memory)
		return (NULL);
	while (i < (size + 1))
	{
		allocated_memory[i] = '\0';
		i++;
	}
	return (allocated_memory);
}
