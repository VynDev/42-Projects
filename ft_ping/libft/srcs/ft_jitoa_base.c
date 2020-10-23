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

static int		get_n_size(uintmax_t value, unsigned int base)
{
	uintmax_t	size;

	size = 0;
	while (value >= base)
	{
		value = value / base;
		size++;
	}
	return (size + 1);
}

char			*ft_jitoa_base(uintmax_t value, unsigned int base)
{
	char		charset[36];
	uintmax_t	i;
	char		*returned_char;

	set_charset(charset);
	i = get_n_size(value, base);
	if ((returned_char = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	returned_char[i] = '\0';
	--i;
	while (i > 0)
	{
		returned_char[i] = charset[value % base];
		value = value / base;
		--i;
	}
	returned_char[i] = charset[value % base];
	return (returned_char);
}
