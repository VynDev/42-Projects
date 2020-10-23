/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_rep			*convert_s(t_convert *convert, va_list *ap)
{
	char	*text;
	t_rep	*rep;

	text = ft_strdup(va_arg(*ap, char *));
	if (text == NULL)
		text = ft_strdup("(null)");
	if (convert->precision != -1
		&& (size_t)convert->precision < ft_strlen(text))
		text[convert->precision] = '\0';
	if (flag_exist(convert, '0') && !flag_exist(convert, '-'))
		text = pad_zero(text, convert->width - ft_strlen(text));
	text = add_width(text,
		convert->width - ft_strlen(text), flag_exist(convert, '-'));
	rep = create_rep(text, ft_strlen(text));
	return (rep);
}
