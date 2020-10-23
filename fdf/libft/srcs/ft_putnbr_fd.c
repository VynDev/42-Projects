/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:29:21 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:29:23 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nombre[10];
	int		i;

	i = 0;
	if (n < 0)
		ft_putchar_fd('-', fd);
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
			ft_putchar_fd('0' + nombre[i], fd);
		else
			ft_putchar_fd('0' + (nombre[i] * -1), fd);
		i--;
	}
}
