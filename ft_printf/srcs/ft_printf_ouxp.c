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

t_rep			*convert_b(t_convert *convert, va_list *ap)
{
	char	*number;
	int		w;
	int		is_zero;
	t_rep	*rep;

	number = preconvert_atoi_base(convert, ap, &w);
	w = 0;
	is_zero = number[0] == '0' ? 1 : 0;
	if (convert->precision == 0 && is_zero)
		number[0] = '\0';
	else
		number = add_precision(number, convert->precision - ft_strlen(number));
	if (flag_exist(convert, '0')
		&& !flag_exist(convert, '-') && convert->precision == -1)
		number = pad_zero(number, (convert->width - ft_strlen(number)) - w);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}

t_rep			*convert_o(t_convert *convert, va_list *ap)
{
	char	*number;
	int		w;
	int		is_zero;
	t_rep	*rep;

	number = preconvert_atoi_base(convert, ap, &w);
	is_zero = number[0] == '0' ? 1 : 0;
	if (convert->precision == 0 && !flag_exist(convert, '#') && is_zero)
		number[0] = '\0';
	else
		number = add_precision(number, convert->precision - ft_strlen(number));
	if (!flag_exist(convert, '#') || is_zero || number[0] == '0')
		w = 0;
	if (flag_exist(convert, '0')
		&& !flag_exist(convert, '-') && convert->precision == -1)
		number = pad_zero(number, (convert->width - ft_strlen(number)) - w);
	if (w != 0 && flag_exist(convert, '#'))
		number = add_prefix(number, convert);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}

t_rep			*convert_u(t_convert *convert, va_list *ap)
{
	char	*number;
	int		w;
	t_rep	*rep;

	number = preconvert_atoi_base(convert, ap, &w);
	w = 0;
	if (convert->precision == 0)
		number[0] = '\0';
	else
		number = add_precision(number, convert->precision - ft_strlen(number));
	if (flag_exist(convert, '0')
		&& !flag_exist(convert, '-') && convert->precision == -1)
		number = pad_zero(number, (convert->width - ft_strlen(number)) - w);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}

t_rep			*convert_x(t_convert *convert, va_list *ap)
{
	char	*number;
	int		w;
	int		is_zero;
	t_rep	*rep;

	number = preconvert_atoi_base(convert, ap, &w);
	is_zero = number[0] == '0' ? 1 : 0;
	if (convert->precision == 0)
		number[0] = '\0';
	else
		number = add_precision(number, convert->precision - ft_strlen(number));
	if (!flag_exist(convert, '#') || is_zero)
		w = 0;
	if (flag_exist(convert, '0')
		&& !flag_exist(convert, '-') && convert->precision == -1)
		number = pad_zero(number, (convert->width - ft_strlen(number)) - w);
	if (w != 0 && flag_exist(convert, '#'))
		number = add_prefix(number, convert);
	if (convert->specifier == 'X')
		ft_strcapitalize(number);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}

t_rep			*convert_p(t_convert *convert, va_list *ap)
{
	char	*number;
	int		w;
	t_rep	*rep;

	w = 0;
	number = preconvert_atoi_base(convert, ap, &w);
	if (convert->precision == 0 && number[0] == '0')
		number[0] = 0;
	else
		number = add_precision(number, convert->precision - ft_strlen(number));
	if (flag_exist(convert, '0') && convert->precision == -1)
		number = pad_zero(number, (convert->width - ft_strlen(number)) - w);
	number = add_to_str(ft_strdup("0x"), number);
	number = add_width(number,
		convert->width - ft_strlen(number), flag_exist(convert, '-'));
	rep = create_rep(number, ft_strlen(number));
	return (rep);
}
