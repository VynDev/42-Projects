/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_rep			*convert_c(t_convert *convert, va_list *ap)
{
	int		i;
	int		flag;
	char	*text;
	t_rep	*rep;

	if (convert->width < 1)
		convert->width = 1;
	text = (char *)malloc(sizeof(char) * convert->width);
	i = 0;
	flag = flag_exist(convert, '-');
	while (i < convert->width - 1)
	{
		if (flag_exist(convert, '0'))
			text[flag + i] = '0';
		else
			text[flag + i] = ' ';
		++i;
	}
	if (flag_exist(convert, '-'))
		text[0] = va_arg(*ap, int);
	else
		text[i] = va_arg(*ap, int);
	rep = create_rep(text, convert->width);
	return (rep);
}

static char		*convert_c_add_width(t_convert *convert, char *temp, int len)
{
	char	*text;

	text = (char *)malloc(sizeof(char) * convert->width);
	if (!text)
		return (NULL);
	if (flag_exist(convert, '-'))
	{
		ft_memcpy(text, temp, len);
		ft_memset(text + len, ' ', convert->width - len);
	}
	else
	{
		ft_memcpy(text + (convert->width - len), temp, len);
		ft_memset(text, ' ', convert->width - len);
	}
	return (text);
}

t_rep			*convert_cmaj(t_convert *convert, va_list *ap)
{
	char	*text;
	t_rep	*rep;
	int		len;
	char	*temp;

	len = ft_wchar_to_char(va_arg(*ap, int), &text);
	if (len < convert->width)
	{
		temp = text;
		text = convert_c_add_width(convert, temp, len);
		free(temp);
	}
	else
		convert->width = len;
	rep = create_rep(text, convert->width);
	return (rep);
}
