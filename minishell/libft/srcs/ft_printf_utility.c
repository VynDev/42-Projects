/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:48 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 09:20:03 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*add_prefix(char *number, t_convert *convert)
{
	if (!number)
		return (NULL);
	if (convert->specifier == 'o')
		return (add_to_str(ft_strdup("0"), number));
	else if (convert->specifier == 'x' || convert->specifier == 'X')
		return (add_to_str(ft_strdup("0x"), number));
	return (number);
}

int		flag_exist(t_convert *convert, char flag)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (convert->flag[i] == flag)
			return (1);
		++i;
	}
	return (0);
}

char	*abs_char(char *number)
{
	char	*new_number;

	if (!number)
		return (NULL);
	if (number[0] != '-' && number[0] != '+')
		return (number);
	new_number = (char *)malloc(sizeof(char) * ft_strlen(number));
	if (!new_number)
		return (NULL);
	ft_strcpy(new_number, number + 1);
	free(number);
	return (new_number);
}

char	*add_to_str(char *str, char *add)
{
	char	*temp;

	if (!add || !str)
		return (NULL);
	temp = str;
	str = ft_strjoin(str, add);
	free(add);
	free(temp);
	return (str);
}

t_rep	*create_rep(char *text, size_t len)
{
	t_rep	*rep;

	rep = (t_rep *)malloc(sizeof(t_rep));
	if (!rep)
		return (NULL);
	rep->text = text;
	rep->len = len;
	return (rep);
}
