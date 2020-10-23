/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*convert_atoi(t_convert *convert, va_list *ap)
{
	char	*number;

	number = NULL;
	if (convert->specifier == 'D')
		number = ft_jitoa((long int)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 0)
		number = ft_jitoa((int)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'h' && convert->length[1] == 'h')
		number = ft_jitoa((signed char)(char)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'l' && convert->length[1] == 'l')
		number = ft_jitoa((long long int)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'h')
		number = ft_jitoa((short int)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'l')
		number = ft_jitoa((long int)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'j')
		number = ft_jitoa((intmax_t)va_arg(*ap, intmax_t));
	else if (convert->length[0] == 'z')
		number = ft_jitoa((size_t)va_arg(*ap, intmax_t));
	return (number);
}

t_rep		*convert_di(t_convert *convert, va_list *ap)
{
	char	*number;
	t_rep	*rep;

	number = convert_atoi(convert, ap);
	if (number[0] == '0' && convert->precision == 0)
		number[0] = '\0';
	else
		number = add_precision(number,
			convert->precision - ft_strlen(number));
	if (flag_exist(convert, '+'))
		number = add_sign(number);
	if (flag_exist(convert, '0')
		&& !flag_exist(convert, '-') && convert->precision == -1)
		number = pad_zero(number,
			(convert->width - ft_strlen(number)) - flag_exist(convert, ' '));
	if (!flag_exist(convert, '+')
		&& flag_exist(convert, ' ') && number[0] != '-')
		number = add_to_str(ft_strdup(" "), number);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}
