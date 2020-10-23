/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:10:34 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:10:44 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include <locale.h>
#include <limits.h>

int		main(void)
{
	setlocale(LC_ALL, "");
	ft_printf("LA FONCTION ft_printf\n");
	printf("Returned value: %d\n", ft_printf("%.p\n", 0));
	ft_printf("LA FONCTIONprintf\n");
	printf("Returned value: %d\n", printf("%.p\n", 0));
	return (0);
}
