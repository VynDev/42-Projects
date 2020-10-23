/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:29:15 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:29:17 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	nombre[10];
	int		i;

	i = 0;
	if (n < 0)
		ft_putchar('-');
	while (n >= 10 || n <= -10)
	{
		nombre[i] = n % 10;
		n = n / 10;
		i++;
	}
	nombre[i] = n;
	while (i >= 0)
	{
		if (n >= 0)
			ft_putchar('0' + nombre[i]);
		else
			ft_putchar('0' + (nombre[i] * -1));
		i--;
	}
}
