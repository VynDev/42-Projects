/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:23:22 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:23:25 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int		get_first_char(const char *nptr)
{
	int		i;

	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\n'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\r'
		|| nptr[i] == '\f' || nptr[i] == '0'))
		i++;
	return (i);
}

static int		get_last_digit(const char *nptr)
{
	int		i;

	i = get_first_char(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(*(nptr + i)))
		i++;
	return (i - 1);
}

int				ft_aisint(const char *nptr)
{
	int			i;
	int			add;
	intmax_t	result;

	i = get_last_digit(nptr);
	if (nptr[get_first_char(nptr)] == '-')
		add = -1;
	else
		add = 1;
	if (add == -1 && ft_strlen(nptr) > 11)
		return (0);
	if (add == 1 && ft_strlen(nptr) > 10)
		return (0);
	result = 0;
	while (i >= 0 && ft_isdigit(nptr[i]))
	{
		result = result + ((nptr[i] - '0') * add);
		add = add * 10;
		i--;
	}
	if (result < INT_MIN || result > INT_MAX)
		return (0);
	return (1);
}
