/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	reset_convert(t_convert *convert)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (i < 5)
			convert->flag[i] = 0;
		convert->length[i] = 0;
		++i;
	}
	convert->width = 0;
	convert->precision = -1;
	convert->specifier = -1;
}

void	fill_convert(t_convert *convert,
	CCR format, t_pcursor *cur, va_list *ap)
{
	int		continuer;

	continuer = 1;
	while (continuer)
	{
		if (isflag(format, cur->i))
			set_flag(convert, format[cur->i]);
		else if (ft_isdigit(format[cur->i]) || format[cur->i] == '*')
			set_width(convert, format, cur, ap);
		else if (format[cur->i] == '.')
			set_precision(convert, format, cur, ap);
		else if (islength(format, cur->i))
			set_length(convert, format[cur->i]);
		else
			convert->specifier = format[cur->i];
		if (format[cur->i] != '\0')
			++(cur->i);
		if (convert->specifier != -1)
			continuer = 0;
	}
	cur->last = cur->i;
}

t_rep	*convert_add_pourcent(t_convert *convert)
{
	t_rep	*rep;
	char	*text;

	text = ft_strdup("%");
	if (flag_exist(convert, '0') && !flag_exist(convert, '-'))
		text = pad_zero(text, convert->width - 1);
	text = add_width(text,
		convert->width - ft_strlen(text), flag_exist(convert, '-'));
	rep = create_rep(text, ft_strlen(text));
	return (rep);
}

t_rep	*convert_bad_spec(t_convert *convert)
{
	char	*text;
	t_rep	*rep;
	int		len;

	text = ft_strnew(1);
	text[0] = convert->specifier;
	if (flag_exist(convert, '0'))
		text = pad_zero(text, convert->width - 1);
	text = add_width(text,
		convert->width - ft_strlen(text), flag_exist(convert, '-'));
	len = convert->specifier == '\0' ? 0 : ft_strlen(text);
	rep = create_rep(text, len);
	return (rep);
}
