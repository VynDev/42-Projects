/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_atoi_base.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*convert_atoi_base(t_convert *convert,
	va_list *ap, int base, char *number)
{
	if (convert->specifier == 'O')
		number = ft_jitoa_base((unsigned long int)va_arg(*ap, uintmax_t), 8);
	else if (convert->specifier == 'U')
		number = ft_jitoa_base((unsigned long int)va_arg(*ap, uintmax_t), 10);
	else if (convert->specifier == 'p')
		number = ft_jitoa_base((unsigned long int)va_arg(*ap, uintmax_t), 16);
	else if (convert->length[0] == 0)
		number = ft_jitoa_base((unsigned int)va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'h' && convert->length[1] == 'h')
		number = ft_jitoa_base((unsigned char)va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'l' && convert->length[1] == 'l')
		number =
	ft_jitoa_base((unsigned long long int)va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'h')
		number =
	ft_jitoa_base((unsigned short int)va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'l')
		number = ft_jitoa_base((unsigned long int)va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'j')
		number = ft_jitoa_base(va_arg(*ap, uintmax_t), base);
	else if (convert->length[0] == 'z')
		number = ft_jitoa_base((size_t)va_arg(*ap, uintmax_t), base);
	return (number);
}

char		*preconvert_atoi_base(t_convert *convert, va_list *ap, int *w)
{
	char	*number;

	number = NULL;
	if (convert->specifier == 'o' || convert->specifier == 'O')
	{
		number = convert_atoi_base(convert, ap, 8, NULL);
		if (convert->specifier == 'O')
			convert->specifier = 'o';
		*w = 1;
	}
	else if (convert->specifier == 'u' || convert->specifier == 'U')
		number = convert_atoi_base(convert, ap, 10, NULL);
	else if (convert->specifier == 'x' || convert->specifier == 'X'
		|| convert->specifier == 'p')
	{
		number = convert_atoi_base(convert, ap, 16, NULL);
		*w = 2;
	}
	else if (convert->specifier == 'b')
	{
		number = convert_atoi_base(convert, ap, 2, NULL);
		*w = 0;
	}
	return (number);
}
