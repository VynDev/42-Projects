/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:28:29 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/04 12:22:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_wchar_to_charnextone(int c, char **str)
{
	if ((*str = (char *)malloc(sizeof(char) * 3)) == NULL)
		return (0);
	*((*str) + 0) = (char)((c >> 12) | 0xE0);
	*((*str) + 1) = (char)(((c >> 6) & 0x3F) | 0x80);
	*((*str) + 2) = (char)((c & 0x3F) | 0x80);
	return (3);
}

static int	ft_wchar_to_charnexttwo(int c, char **str)
{
	if ((*str = (char *)malloc(sizeof(char) * 4)) == NULL)
		return (0);
	*((*str) + 0) = (char)((c >> 18) | 0xF0);
	*((*str) + 1) = (char)(((c >> 12) & 0x3F) | 0x80);
	*((*str) + 2) = (char)(((c >> 6) & 0x3F) | 0x80);
	*((*str) + 3) = (char)((c & 0x3F) | 0x80);
	return (4);
}

int			ft_wchar_to_char(int c, char **str)
{
	if (c <= 127)
	{
		if ((*str = (char *)malloc(sizeof(char) * 1)) == NULL)
			return (0);
		**str = (char)c;
		return (1);
	}
	else if (c <= 2047)
	{
		if ((*str = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (0);
		*((*str) + 0) = (char)((c >> 6) | 0xC0);
		*((*str) + 1) = (char)((c & 0x3F) | 0x80);
		return (2);
	}
	else if (c <= 65535)
		return (ft_wchar_to_charnextone(c, str));
	else if (c <= 2097151)
		return (ft_wchar_to_charnexttwo(c, str));
	return (0);
}
