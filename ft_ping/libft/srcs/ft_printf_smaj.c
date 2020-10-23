/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_smaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char		*add_to_wstr(char *str, char *add, int *len, int len_temp)
{
	char		*temp;

	temp = str;
	str = (char *)malloc(sizeof(char) * (*len + len_temp));
	ft_memcpy(str, temp, *len);
	ft_memcpy(str + *len, add, len_temp);
	if (temp)
		free(temp);
	if (add)
		free(add);
	return (str);
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
	free(temp);
	return (text);
}

static int		fill_text(char **text, int *wstr, t_convert *convert, int *len)
{
	int		len_temp;
	char	*c;

	len_temp = ft_wchar_to_char(*wstr, &c);
	if (convert->precision != -1)
	{
		if (*len + len_temp <= convert->precision)
		{
			*text = add_to_wstr(*text, c, len, len_temp);
		}
		else
		{
			if (!*text)
				*text = ft_strdup("");
			free(c);
			return (0);
		}
	}
	else
	{
		*text = add_to_wstr(*text, c, len, len_temp);
	}
	*len += len_temp;
	return (1);
}

static void		add_zero_width(t_convert *convert, char **text, int *len)
{
	if (flag_exist(convert, '0'))
	{
		*text = pad_zero(*text, convert->width - *len);
		*len = convert->width;
	}
	if (*len < convert->width)
	{
		*text = convert_c_add_width(convert, *text, *len);
		*len = convert->width;
	}
}

t_rep			*convert_smaj(t_convert *convert, va_list *ap)
{
	char	*text;
	int		*wstr;
	int		ret;
	int		len;

	text = NULL;
	len = 0;
	ret = 1;
	wstr = va_arg(*ap, int *);
	if (!wstr)
	{
		text = ft_strdup("(null)");
		len = convert->precision != -1
		&& convert->precision < 6 ? convert->precision : 6;
	}
	while (wstr && *wstr != 0 && ret)
	{
		ret = fill_text(&text, wstr, convert, &len);
		wstr++;
	}
	add_zero_width(convert, &text, &len);
	return (create_rep(text, len));
}
