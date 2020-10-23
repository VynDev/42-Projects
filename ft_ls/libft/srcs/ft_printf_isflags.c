/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_addflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		islength(CCR format, int i)
{
	char	*speci;
	int		j;

	speci = "hlljz";
	j = 0;
	while (j < 5)
	{
		if (format[i] == speci[j])
			return (1);
		++j;
	}
	return (0);
}

int		isspecifier(CCR format, int i)
{
	char	*speci;
	int		j;

	speci = "%sSpdDioOuUxXcC";
	j = 0;
	while (j < 15)
	{
		if (format[i] == speci[j])
			return (1);
		++j;
	}
	return (0);
}

int		isflag(CCR format, int i)
{
	char	*flags;
	int		j;

	flags = "-+ #0";
	j = 0;
	while (j < 5)
	{
		if (format[i] == flags[j])
			return (1);
		++j;
	}
	return (0);
}
