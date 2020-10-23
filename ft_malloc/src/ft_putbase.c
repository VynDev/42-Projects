/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:39:53 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 11:39:56 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_charset(char *charset)
{
	int		i;

	i = 0;
	while (i < 10)
	{
		charset[i] = '0' + i;
		++i;
	}
	i = 0;
	while (i < 26)
	{
		charset[10 + i] = 'a' + i;
		++i;
	}
}

void			ft_putbase(uintmax_t value, unsigned int base)
{
	char		charset[36];

	set_charset(charset);
	if (value / base > 0)
		ft_putbase(value / base, base);
	ft_putchar(charset[value % base]);
}
