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

#include <stdlib.h>

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

static int		absl(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static int		get_n_size(int value, int base, int *is_negative)
{
	int		size;

	if (value >= 0 || base != 10)
	{
		size = 0;
		*is_negative = 0;
	}
	else
	{
		size = 1;
		*is_negative = 1;
	}
	while (value >= base || value <= -base)
	{
		value = value / base;
		size++;
	}
	size++;
	return (size);
}

char			*ft_itoa_base_n(int value, int base)
{
	char	charset[36];
	int		i;
	char	*returned_char;
	int		is_negative;

	set_charset(charset);
	i = get_n_size(value, base, &is_negative);
	if ((returned_char = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	if (value < 0 && base == 10)
	{
		returned_char[0] = '-';
		is_negative = 1;
	}
	returned_char[i] = '\0';
	--i;
	while (i >= 0)
	{
		if (i == 0 && is_negative)
			return (returned_char);
		returned_char[i] = charset[absl(value % base)];
		value = value / base;
		--i;
	}
	return (returned_char);
}
