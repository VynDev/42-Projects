/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_isflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	set_width(t_convert *convert, CCR format, t_pcursor *cur, va_list *ap)
{
	if (format[cur->i] == '*')
	{
		convert->width = va_arg(*ap, int);
		if (convert->width < 0)
		{
			convert->width = -convert->width;
			set_flag(convert, '-');
		}
	}
	else
	{
		convert->width = ft_atoi(format + cur->i);
		while (ft_isdigit(format[cur->i + 1]))
			++(cur->i);
	}
}

void	set_precision(t_convert *convert, CCR format,
	t_pcursor *cur, va_list *ap)
{
	if (format[cur->i + 1] == '*')
	{
		convert->precision = va_arg(*ap, int);
		if (convert->precision < 0)
			convert->precision = -1;
		++(cur->i);
	}
	else if (ft_isdigit(format[cur->i + 1]))
	{
		++(cur->i);
		convert->precision = ft_atoi(format + cur->i);
		while (ft_isdigit(format[cur->i + 1]))
			++(cur->i);
	}
	else
	{
		convert->precision = 0;
	}
}

void	set_length(t_convert *convert, char length)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (convert->length[i] == 0)
		{
			convert->length[i] = length;
			return ;
		}
		++i;
	}
	convert->length[0] = 0;
	convert->length[1] = 0;
	set_length(convert, length);
}

void	set_flag(t_convert *convert, char flag)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (convert->flag[i] == flag)
			return ;
		if (convert->flag[i] == 0)
		{
			convert->flag[i] = flag;
			return ;
		}
		++i;
	}
}
