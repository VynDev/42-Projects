/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:26:10 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:26:12 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	size_t		i;
	void		*allocated_memory;

	i = 0;
	allocated_memory = (void *)malloc(size);
	if (!allocated_memory)
		return (NULL);
	while (i < size)
	{
		*((unsigned char *)allocated_memory + i) = 0;
		i++;
	}
	return (allocated_memory);
}
