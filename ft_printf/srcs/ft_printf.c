/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static t_rep	*convertnext(t_convert *convert, va_list *ap)
{
	t_rep		*rep;

	rep = NULL;
	if (convert->specifier == 'C' ||
		(convert->specifier == 'c' && convert->length[0] == 'l'))
		rep = convert_cmaj(convert, ap);
	else if (convert->specifier == 'c')
		rep = convert_c(convert, ap);
	else if (convert->specifier == 'p')
		rep = convert_p(convert, ap);
	else if (convert->specifier == 'b')
		rep = convert_b(convert, ap);
	else if (convert->specifier == '%')
		rep = convert_add_pourcent(convert);
	else
		rep = convert_bad_spec(convert);
	return (rep);
}

t_rep			*convert(CCR format, t_pcursor *cur, va_list *ap)
{
	t_convert	convert;
	t_rep		*rep;

	rep = NULL;
	reset_convert(&convert);
	++(cur->i);
	fill_convert(&convert, format, cur, ap);
	if (convert.specifier == 'd' ||
		convert.specifier == 'i' || convert.specifier == 'D')
		rep = convert_di(&convert, ap);
	else if (convert.specifier == 'o' || convert.specifier == 'O')
		rep = convert_o(&convert, ap);
	else if (convert.specifier == 'u' || convert.specifier == 'U')
		rep = convert_u(&convert, ap);
	else if (convert.specifier == 'x' || convert.specifier == 'X')
		rep = convert_x(&convert, ap);
	else if (convert.specifier == 'S' ||
		(convert.specifier == 's' && convert.length[0] == 'l'))
		rep = convert_smaj(&convert, ap);
	else if (convert.specifier == 's')
		rep = convert_s(&convert, ap);
	else
		return (convertnext(&convert, ap));
	return (rep);
}

int				add_to_finalstr(char **str, char *add, int str_len, int add_len)
{
	char	*temp;

	temp = *str;
	*str = (char *)malloc(sizeof(char) * (str_len + add_len));
	if (temp)
		ft_memcpy(*str, temp, str_len);
	ft_memcpy(*str + str_len, add, add_len);
	if (temp)
		free(temp);
	if (add)
		free(add);
	return (str_len + add_len);
}

char			*do_stuff(CCR format, t_pcursor *cur, va_list *ap, int *len)
{
	t_rep	*rep;
	char	*str;

	str = NULL;
	while (format[cur->i])
	{
		if (format[cur->i] == '{')
			add_color(format, cur, len, &str);
		else if (format[cur->i] == '%')
		{
			*len = add_to_finalstr(&str, ft_strsub(format,
				cur->last, cur->i - cur->last), *len, cur->i - cur->last);
			rep = convert(format, cur, ap);
			if (rep)
			{
				*len = add_to_finalstr(&str, rep->text, *len, rep->len);
				free(rep);
			}
		}
		else
			++(cur->i);
	}
	*len = add_to_finalstr(&str, ft_strsub(format,
		cur->last, cur->i - cur->last), *len, cur->i - cur->last);
	return (str);
}

int				ft_printf(const char *restrict format, ...)
{
	int			len;
	t_pcursor	cur;
	va_list		ap;
	char		*str;

	va_start(ap, format);
	cur.last = 0;
	cur.i = 0;
	len = 0;
	if ((str = do_stuff(format, &cur, &ap, &len)) != NULL)
	{
		ft_putnstr(str, len);
		free(str);
		va_end(ap);
		return (len);
	}
	return (len);
}
