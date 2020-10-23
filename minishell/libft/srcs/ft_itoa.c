/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:24:54 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:38:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		absl(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static int		get_n_size(int n)
{
	int		size;

	if (n >= 0)
		size = 0;
	else
		size = 1;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*returned_char;

	i = get_n_size(n);
	returned_char = (char *)malloc(sizeof(char) * (i + 1));
	if (!returned_char)
		return (NULL);
	if (n < 0)
		returned_char[0] = '-';
	returned_char[i] = '\0';
	i--;
	while (n >= 10 || n <= -10)
	{
		returned_char[i] = '0' + absl(n % 10);
		n = n / 10;
		i--;
	}
	returned_char[i] = '0' + absl(n);
	return (returned_char);
}
