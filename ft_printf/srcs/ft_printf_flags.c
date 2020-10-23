/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*add_sign(char *number)
{
	if (number[0] == '-')
		return (number);
	return (add_to_str(ft_strdup("+"), number));
}

char	*add_width(char *number, int width, int direction)
{
	int		i;
	char	*temp;

	if (width <= 0)
		return (number);
	i = 0;
	temp = ft_strnew(width);
	while (i < width)
	{
		temp[i] = ' ';
		++i;
	}
	if (direction == 0)
		return (add_to_str(temp, number));
	else
		return (add_to_str(number, temp));
}

char	*pad_zero(char *number, int nb_zero)
{
	char	*temp;
	int		negative;

	if (nb_zero <= 0)
		return (number);
	negative = 0;
	if (number[0] == '-')
		negative = 1;
	else if (number[0] == '+')
		negative = -1;
	number = abs_char(number);
	temp = ft_strnew(nb_zero);
	ft_memset(temp, '0', nb_zero);
	temp = add_to_str(temp, number);
	if (negative == 1)
		temp = add_to_str(ft_strdup("-"), temp);
	else if (negative == -1)
		temp = add_to_str(ft_strdup("+"), temp);
	return (temp);
}

char	*add_precision(char *number, int precision)
{
	int		i;
	char	*temp;
	int		negative;

	negative = 0;
	if (number[0] == '-')
		negative = 1;
	if (precision + negative <= 0)
		return (number);
	number = abs_char(number);
	i = 0;
	temp = ft_strnew(precision + negative);
	while (i < precision + negative)
	{
		temp[i] = '0';
		++i;
	}
	temp = add_to_str(temp, number);
	if (negative)
		temp = add_to_str(ft_strdup("-"), temp);
	return (temp);
}
